# Mouse Events

There are the following cases of mouse events, enumerated for 

1. Nothing drawn: Need to make pen or scribble tool as default.

**Shape mouse:**

1. Nothing selected: Can select shapes and curves
   1. Single click: rectangular selection
   2. Double click: path selection
2. Something selected: 
   1. If a rescale or move button is clicked, then rescale or move
   2. If not, behave as if nothing was selected.

**Vector Mouse:** Can only select curves when nothing is selected

1. Nothing selected: Only select curves
   1. Single click: rectangular selection
   2. Double click: path selection
2. Curves selected: show nodes
   1. If double-clicked near curve, add node
      1. Mouse moved: Move node
   2. Nodes selected: show vectors
      1. Mouse moved: Move node
3. Node selected: show vectors
   1. If double clicked on a selected node, make symmetrical
   2. Vectors selected
      1. Mouse moved: Vector heads

## Current Errors

Double clicking on a `selection rect` with selected items seems to treat old selection rect as a new one.

> **Resolve:** ~~Not sure what's causing the bug. Not too serious anyways. We can try to `qDebug()` all over the code to see whether it skips an expected step.~~
>
> Actually, more serious than I thought. The problem persists when nothing is clicked.

Nodes not selecting during node/vector selection.

> Really haven't tried anything yet on this.
>
> **Resolve:** 