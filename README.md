Fork of [neovim-qt](https://github.com/equalsraf/neovim-qt).

## Changes

- `set guifont` use `force` like `GuiFont!` in default.

## FAQ

- 'Unable to find the platform plugin' when build with mingw

Change the target `build src/gui/CMakeFiles/windeployqt` in `build.ninja` generate by cmake:

from `cd /D <path-to-build-of-neovim-qt>\src\gui` to `cd /D <path-to-windeployqt>`.
