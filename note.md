# Lab 2 Note - Git Commands and GitHub Actions

The objective of this practical assignment is to manipulate and understand advanced Git functionalities, including cherry-picking, rebasing, pull requests, hooks, and GitHub Actions CI/CD workflows.

---

## Setup: Fork and Clone the Repository

> **Assignment** - Fork the repository [https://github.com/QLOG-5EII/sobel_morpho](https://github.com/QLOG-5EII/sobel_morpho) to your GitHub account, clone it locally, and create a working branch.

### Steps Completed

1. **Fork the repository using GitHub CLI:**
   ```bash
   gh repo fork QLOG-5EII/sobel_morpho --clone=true --remote=true lab2_git
   ```
   
   This command:
   - Creates a fork at `Sachatms/sobel_morpho` on GitHub
   - Clones the fork into the `lab2_git` folder
   - Sets up two remotes:
     - `origin` → Your fork (`sachatms/sobel_morpho`)
     - `upstream` → Original repo (`QLOG-5EII/sobel_morpho`)

2. **Create a working branch:**
   ```bash
   cd lab2_git
   git checkout -b workspace_sacha
   ```

3. **Verify the setup:**
   ```bash
   git branch -a
   ```
   
   Available branches:
   - `main` (local, current base)
   - `workspace_sacha` (local, working branch) ✅
   - `remotes/origin/main` (your fork)
   - `remotes/origin/other-branch` (your fork)
   - `remotes/upstream/main` (original repo)
   - `remotes/upstream/other-branch` (original repo - **to be cherry-picked later**)

### Repository Structure

The project is a C-based image processing application that applies Sobel/Dilation/Erosion filters to video:

```
lab2_git/
├── CMakeLists.txt          # CMake build configuration
├── README.md               # Project documentation
└── src/
    ├── main.c              # Main entry point
    ├── sobel.c             # Sobel filter implementation
    ├── sobel.h             # Sobel filter header
    ├── yuvRead.c           # YUV video reading
    ├── yuvRead.h
    ├── yuvDisplay.c        # SDL2-based video display
    └── yuvDisplay.h
```

---

## Part 1: Cherry-Pick from Another Branch

> **Assignment** - Retrieve a commit from the `other-branch` and copy it to your working branch using `git cherry-pick`, then rename the commit using `git rebase -i`.

### TODO

1. **List commits in `other-branch`:**
   ```bash
   git log upstream/other-branch --oneline
   ```
   
   Identify the commit named "temp" to cherry-pick.

2. **Cherry-pick the commit:**
   ```bash
   git cherry-pick <commit-hash>
   ```

3. **Rename the commit using interactive rebase:**
   ```bash
   git rebase -i HEAD~1
   ```
   
   In the editor:
   - Change `pick` to `reword` (or `r`)
   - Save and close
   - Edit the commit message to something meaningful (e.g., "Fix: Add missing functionality")

> **Note:** Alternatively, use `git cherry-pick --edit <commit-hash>` to edit the message immediately.

---

## Part 2: Modify the Sobel Filter

> **Assignment** - Modify the Sobel filter in `src/sobel.c` to implement a different filter (e.g., mean/average filter), commit the changes, push to your fork, and create a pull request.

### TODO

1. **Modify `src/sobel.c`:**
   - Replace the Sobel filter implementation with a mean/average filter
   - Example: Replace gradient calculation with averaging of neighboring pixels

2. **Create a commit:**
   ```bash
   git add src/sobel.c
   git commit -m "feat: Replace Sobel filter with mean averaging filter"
   ```

3. **Push to your fork:**
   ```bash
   git push origin workspace_sacha
   ```

4. **Create a pull request:**
   - Go to the original repository: [https://github.com/QLOG-5EII/sobel_morpho](https://github.com/QLOG-5EII/sobel_morpho)
   - Click "New Pull Request"
   - Select: `base: main` ← `compare: sachatms:workspace_sacha`
   - Add title and description
   - Submit the PR

---

## Part 3: Pre-Commit Hook for Code Formatting

> **Assignment** - Create a Git hook that verifies all staged files are properly formatted using `clang-format` before allowing a commit.

### Hook Script (`pre-commit`)

```bash
#!/bin/bash

# Get the root directory of the Git repository
root=$(git rev-parse --show-toplevel)

# Get the list of staged files
list=$(git diff --name-only --cached)

# Flag to track if any files are incorrectly formatted
formatted_incorrectly=0

# Iterate over each staged file
while IFS= read -r file; do
    # Skip empty lines
    if [ -z "$file" ]; then
        continue
    fi
    
    # Only check C/C++ files
    if [[ "$file" =~ \.(c|cpp|h|hpp)$ ]]; then
        # Get the formatted version of the file
        formatted=$(clang-format "$root/$file")
        
        # Get the current content of the file
        current=$(cat "$root/$file")
        
        # Compare formatted vs current
        if [ "$formatted" != "$current" ]; then
            echo "Error: File $file is not properly formatted"
            formatted_incorrectly=1
        fi
    fi
done <<< "$list"

# Exit with error if any files are incorrectly formatted
if [ $formatted_incorrectly -eq 1 ]; then
    echo ""
    echo "Please run 'clang-format -i' on the above files before committing"
    exit 1
fi

exit 0
```

### Installation

1. **Create the hook:**
   ```bash
   cp .git/hooks/pre-commit.sample .git/hooks/pre-commit
   # Replace the content with the script above
   ```

2. **Make it executable:**
   ```bash
   chmod +x .git/hooks/pre-commit
   ```

### Sharing Hooks Across the Team

**Problem:** Hooks in `.git/hooks/` are not versioned by Git.

**Solutions:**

1. **Store hooks in a versioned directory:**
   ```bash
   mkdir -p .githooks
   # Move your pre-commit script to .githooks/pre-commit
   git add .githooks/pre-commit
   git commit -m "chore: Add pre-commit formatting hook"
   ```
   
   **Setup instructions for team members:**
   ```bash
   # After cloning, configure Git to use the custom hooks directory
   git config core.hooksPath .githooks
   ```

2. **Add setup script in `README.md`:**
   ```markdown
   ## Development Setup
   
   After cloning the repository, run:
   ```bash
   git config core.hooksPath .githooks
   ```

3. **Use a tool like `husky` (for Node.js projects) or create an install script:**
   ```bash
   #!/bin/bash
   # setup-hooks.sh
   cp .githooks/pre-commit .git/hooks/pre-commit
   chmod +x .git/hooks/pre-commit
   echo "Hooks installed successfully!"
   ```

---

## Part 4: GitHub Actions - CI/CD Workflow

> **Assignment** - Set up GitHub Actions workflows to automatically build and test the project on Ubuntu and Windows for every push and manual trigger.

### Workflow 1: Ubuntu CI

Create `.github/workflows/ubuntu-ci.yml`:

```yaml
name: Ubuntu CI
on: 
  push:
  workflow_dispatch:

jobs:
  build-ubuntu:
    runs-on: ubuntu-latest
    steps:
    - name: Checkout repository
      uses: actions/checkout@v4
      
    - name: Install dependencies
      run: |
        sudo apt-get update
        sudo apt-get install -y cmake build-essential libsdl2-dev clang-format
        
    - name: Build project
      run: |
        mkdir build
        cd build
        cmake ..
        make
        
    - name: Run program
      run: |
        cd build
        ./sobel_morpho
```

### Workflow 2: Multi-OS CI (Matrix Strategy)

Create `.github/workflows/multi-os-ci.yml`:

```yaml
name: Multi-OS CI
on: 
  push:
  workflow_dispatch:

jobs:
  build:
    runs-on: ${{ matrix.os }}
    strategy:
      matrix:
        os: [ubuntu-latest, windows-latest]
    
    steps:
    - name: Checkout repository
      uses: actions/checkout@v4
      
    - name: Install dependencies (Ubuntu)
      if: matrix.os == 'ubuntu-latest'
      run: |
        sudo apt-get update
        sudo apt-get install -y cmake build-essential libsdl2-dev
        
    - name: Install dependencies (Windows)
      if: matrix.os == 'windows-latest'
      run: |
        # Windows dependencies (if needed)
        choco install cmake
        
    - name: Build project
      run: |
        mkdir build
        cd build
        cmake ..
        cmake --build .
        
    - name: Run program
      run: |
        cd build
        ./sobel_morpho
```

### TODO: Add Unit Tests

1. **Create test files:**
   - `tests/test_sobel.c`
   - `tests/test_dilation.c`
   - `tests/test_erosion.c`

2. **Modify `CMakeLists.txt`:**
   ```cmake
   enable_testing()
   
   add_executable(test_sobel tests/test_sobel.c src/sobel.c)
   add_test(NAME SobelTest COMMAND test_sobel)
   ```

3. **Add test step to workflow:**
   ```yaml
   - name: Run unit tests
     run: |
       cd build
       ctest --output-on-failure
   ```

---

## Summary

This lab demonstrates:

- ✅ **Forking and cloning** repositories with GitHub CLI
- ✅ **Remote management** (origin vs upstream)
- ✅ **Branch creation** and switching
- ⏳ **Cherry-picking commits** between branches
- ⏳ **Interactive rebasing** to rewrite history
- ⏳ **Pull requests** from forks
- ⏳ **Git hooks** for enforcing code quality
- ⏳ **GitHub Actions** for CI/CD automation
- ⏳ **Multi-OS testing** with matrix strategies
- ⏳ **Unit testing** integration

> [!TIP]
> **Useful Git Commands:**
>
> ```bash
> # View commit history
> git log --oneline --graph --all
> 
> # Cherry-pick with edit
> git cherry-pick --edit <commit-hash>
> 
> # Interactive rebase (last 3 commits)
> git rebase -i HEAD~3
> 
> # Push new branch to remote
> git push -u origin <branch-name>
> 
> # Configure custom hooks directory
> git config core.hooksPath .githooks
> ```

> [!NOTE]
> **Legend:**
> - ✅ Completed
> - ⏳ To be done
