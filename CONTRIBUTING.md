# Contributing Guide

Please follow these streamlined steps to contribute to this project.

## Issues & PRs
* **Issues:** Check existing ones first. Describe bugs or features clearly.
* **PRs:** Fork, create a branch, commit with clear messages, push, and submit a PR.

## Directory Structure (`./src`)

### New Section
Create a folder inside `./src` using the format: `./[Numbering]_Section_Name`.
* *Example:* `011_Contest_Rules` renders as `Contest Rules` (underscores become spaces).
* *Sorting:* Folders are sorted in lexicographical order. Numbering dictates the order but is dropped from display.
* *Case-sensitivity:* Names are case-sensitive (`002_aBcD` displays as `aBcD`).

### New Subsection
Create any `.tex` file inside your section folder formatted exactly as follows:

```latex
% Subsection name (Supports \(\LaTeX,\) must escape \& and \_)

Main text goes here. Explain algorithms, usage, or notes.
\(\begin{lstlisting}
// C++ source code only
\end{lstlisting}\)

Use \lstinline|inline code| for inline snippets.
```

## Local Build Process
To generate the final PDF, navigate to the root directory `./` and run:
```bash
./make.sh
```
* **Prerequisites:** Ensure both **TeX Live** and **Python** are installed and added to your system's **PATH** environment variable.
