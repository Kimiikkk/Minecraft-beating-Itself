# Replay v3

The browser consumes generated event snapshots.

Each event contains:
- `year`
- `type`
- `stage`
- event coordinates and secondary coordinates
- actor and target IDs
- `count`
- `amount`
- `distance`
- `outpost`
- `note`
- complete `state`
- current outpost statistics
- current entity list

### Pumpkin provenance

`pumpkin_picked` contains:
- source `outpost`
- source coordinates
- `distance` to the End Portal
- cumulative pumpkin count
- actor Enderman ID

### Dragon damage

Every `dragon_damage` event contains:
- event year
- dragon actor ID
- damage amount
- dragon coordinates
- state snapshot with remaining HP

Thus the website can reconstruct a complete damage history rather than only
displaying the final result.
