// Export the pseudo-C of every function, one file per class/namespace.
// Usage (headless): -postScript ExportDecomp.java <output dir>
//@category Export

import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileOptions;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.decompiler.parallel.DecompileConfigurer;
import ghidra.app.decompiler.parallel.DecompilerCallback;
import ghidra.app.decompiler.parallel.ParallelDecompiler;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.Namespace;
import ghidra.program.model.symbol.Symbol;
import ghidra.util.task.TaskMonitor;

import java.io.IOException;
import java.io.Writer;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;

public class ExportDecomp extends GhidraScript {

    private record Entry(Path file, long address, String text) {}

    @Override
    protected void run() throws Exception {
        Path outDir = Paths.get(getScriptArgs()[0]).toAbsolutePath();

        List<Function> functions = new ArrayList<>();
        for (Function f : currentProgram.getFunctionManager().getFunctions(true)) {
            if (!f.isThunk() && !f.isExternal()) {
                functions.add(f);
            }
        }
        println("Decompiling " + functions.size() + " functions");

        DecompileConfigurer configurer = decompiler -> {
            DecompileOptions options = new DecompileOptions();
            options.grabFromProgram(currentProgram);
            decompiler.setOptions(options);
            decompiler.toggleCCode(true);
            decompiler.toggleSyntaxTree(false);
            decompiler.setSimplificationStyle("decompile");
        };

        DecompilerCallback<Entry> callback = new DecompilerCallback<>(currentProgram, configurer) {
            @Override
            public Entry process(DecompileResults results, TaskMonitor m) {
                Function f = results.getFunction();
                String code = results.decompileCompleted()
                        ? results.getDecompiledFunction().getC()
                        : "/* decompilation failed: " + results.getErrorMessage() + " */\n";
                StringBuilder header = new StringBuilder();
                header.append("// ").append(f.getEntryPoint())
                        .append("  size 0x").append(Long.toHexString(f.getBody().getNumAddresses()));
                String mangled = mangledName(f);
                if (mangled != null) {
                    header.append("  ").append(mangled);
                }
                header.append('\n');
                return new Entry(fileFor(outDir, f), f.getEntryPoint().getOffset(), header + code.strip() + "\n");
            }
        };

        List<Entry> entries;
        try {
            entries = ParallelDecompiler.decompileFunctions(callback, functions, monitor);
        } finally {
            callback.dispose();
        }

        Map<Path, List<Entry>> byFile = new TreeMap<>();
        for (Entry e : entries) {
            if (e != null) {
                byFile.computeIfAbsent(e.file(), k -> new ArrayList<>()).add(e);
            }
        }
        for (Map.Entry<Path, List<Entry>> file : byFile.entrySet()) {
            file.getValue().sort(Comparator.comparingLong(Entry::address));
            write(file.getKey(), file.getValue());
        }
        println("Wrote " + byFile.size() + " files to " + outDir);
    }

    private String mangledName(Function f) {
        for (Symbol s : currentProgram.getSymbolTable().getSymbols(f.getEntryPoint())) {
            if (s.getName().startsWith("_Z")) {
                return s.getName();
            }
        }
        return null;
    }

    private static Path fileFor(Path outDir, Function f) {
        List<String> parts = new ArrayList<>();
        for (Namespace ns = f.getParentNamespace(); ns != null && !ns.isGlobal(); ns = ns.getParentNamespace()) {
            parts.add(0, sanitize(ns.getName()));
        }
        if (parts.isEmpty()) {
            return outDir.resolve("_global.cpp");
        }
        Path dir = outDir;
        for (String p : parts.subList(0, parts.size() - 1)) {
            dir = dir.resolve(p);
        }
        return dir.resolve(parts.get(parts.size() - 1) + ".cpp");
    }

    private static String sanitize(String name) {
        String s = name.replaceAll("[^A-Za-z0-9_.-]", "_");
        return s.length() > 120 ? s.substring(0, 120) + "_" + Integer.toHexString(name.hashCode()) : s;
    }

    private static void write(Path file, List<Entry> entries) throws IOException {
        Files.createDirectories(file.getParent());
        try (Writer w = Files.newBufferedWriter(file, StandardCharsets.UTF_8)) {
            for (Entry e : entries) {
                w.write(e.text());
                w.write('\n');
            }
        }
    }
}
