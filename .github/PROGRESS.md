# Publishing progress

The `Publish progress` GitHub Actions workflow sends the README's progress
snapshot to [decompilati.onl](https://decompilati.onl) for game version `1.0.0`.
It runs when the README or reporting configuration changes on `main`, and can
also be started manually from the Actions tab on `main`.

Pull requests generate the JSON and upload it as the `progress-preview` artifact.
Open the workflow run from the PR checks to download and inspect the report.
By default, API submission runs after merging to `main`.

## Test a real submission before merging

After configuring `DECOMP_API_KEY`, add the `publish-progress` label to the PR
(create the label in the repository first if necessary). This starts a workflow
run that submits the report to the real site, using the PR head commit. It
changes the project's public progress; this is not a sandbox submission.
Only PRs with a branch in this repository can publish; fork PRs cannot.

Verify that **Send progress to decompilati.onl** runs and returns an API status
such as `updated` or `unchanged`. Further pushes also publish while the label
is present. Remove the label to return to preview-only behavior. To retry a
submission, remove and re-add the label.

## One-time configuration

1. Sign in to decompilati.onl with GitHub and register `KevinBonnoron/xc2-decomp`
   at <https://decompilati.onl/dashboard/new>. Registration requires a cover image.
2. Copy the project's API key into this repository's **Settings → Secrets and
   variables → Actions → New repository secret**, named `DECOMP_API_KEY`.
   Do not commit the key.
3. Push the workflow to `main`, or start **Publish progress → Run workflow**
   after adding the secret.

## Updating the numbers

Run `check --readme` in the local Nix development shell with the extracted game
binary available, then commit and push the updated README alongside your code.
The checker only updates the README after successful verification. CI sends
that snapshot; it does not recalculate progress when only C++ sources change.
The reported commit identifies the commit containing the snapshot.

Preview the payload without credentials or network access:

```sh
python3 tools/progress.py
```

The report includes matching code bytes and function counts. It does not claim
data progress, fully linked code, or partially matching code that the checker
does not measure. The workflow needs neither Nix nor game files or console keys.

API reference: <https://decompilati.onl/docs/getting-started> and
<https://decompilati.onl/docs/report-format>.
