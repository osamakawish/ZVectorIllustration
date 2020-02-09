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

## Typical Causes for Error

The errors are likely a result of misunderstanding how the code works during a double click:

1. Mouse Pressed (Press = true)
2. Release (Press = false)
3. Double Click (Press is false)
4. Release

## Current Goal

### Transformations of Selected Items

The cleanest and nicest way to do this, after considering various possibilities, is this:

```c++
template<class S, class T>
class Selection {
    typedef QGraphicsItem TransformButton;
    typedef void (Selection::*Transform)(QPoint);
    // NOTE: Move selection rect to 1 less than max numeric value, and these to max.
    QSet<TransformButton *> SCALE_BUTTONS; TransformButton *MOVE_BUTTON;
    TransformButton *SELECTED_BUTTON;
    Transform TRANSFORM_BY;
    
    ...
    
    // True if item is to be transformed, and prepares transformation, false otherwise.
    // Transforms if the item clicks a transform button.
    bool setTransform(QPoint pt) {
        QGraphicsItem *item = SCENE.item(pt);
        if (SCALE_BUTTONS.keys().contains(item)) 
        { SELECTED_BUTTON = item; TRANSFORM_BY = &Selection::rescaleBy; return true; }
        else if (item == MOVE_BUTTON) 
        { SELECTED_BUTTON = item; TRANSFORM_BY = &Selection::moveBy; return true; }
        else { SELECTED_BUTTON = nullptr; return false; }
    }
    bool shouldTransform() {return SELECTED_BUTTON != nullptr;}
    void rescaleBy(QPoint) { ... }
    void moveBy(QPoint) { ... }
    void transformBy(QPoint pt) {(this->*TRANSFORM)(pt);}
    
    ...
    
}
```

