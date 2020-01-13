# Bugs

## Curve `pos()` not centered

### Solution

The solution is straightforward: need to make changes to how everything is drawn.

## Curve not included in selection area

### Solution

If Qt's own classes won't work properly, use the `SelectionRect` to update it. It's tedious that it doesn't work properly, since moving requires properly keeping track of all the information yourself now, but we can report this to Qt at best.