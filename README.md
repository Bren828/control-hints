

# control-hints
A library for creating control hints as TextDraw elements in Pawn (SA-MP).

![Crosshair](https://raw.githubusercontent.com/Bren828/control-hints/main/preview.gif)

## Installation

Include in your code and begin using the library:
```pawn
#include <control-hints>
```

## Example
```pawn
CreateControlHint(playerid, 20.0, 150.0, "Inventory", "I", .show = CH_SHOW_HINT, .textAlignment = CH_TEXT_ALIGN_LEFT, .selectable = 0);
CreateControlHintBelow(playerid, 0.0, 5.0, "Phone", "P", .show = CH_SHOW_HINT, .textAlignment = CH_TEXT_ALIGN_LEFT, .selectable = 0);
```
### Example with animation
```pawn
new HintInventory[MAX_PLAYERS];

HintInventory[playerid] = CreateControlHint(playerid, 20.0, 150.0, "Inventory", "I", .show = CH_SHOW_HINT, .textAlignment = CH_TEXT_ALIGN_LEFT, .selectable = 0);

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {

	if(newkeys == KEY_WALK) {
		StartControlHintAnimation(playerid, HintInventory[playerid], 0xFFFFFFFF, .speed = 15.0);
		return 1;
	}

	if(oldkeys == KEY_WALK) {

		if(IsControlHintAnimating(playerid, HintInventory[playerid])) {
			StopControlHintAnimation(playerid, HintInventory[playerid]);
		}
		return 1;
    }

	return 1;
}

forward OnPlayerControlHintAnimationEnd(playerid, hintid);
public OnPlayerControlHintAnimationEnd(playerid, hintid) {
	
	if(hintid == HintInventory[playerid]) {
		SendClientMessage(playerid, 0xFF00FFAA, "Animation ended");
	}
	return 1;
}
```

## Functions
<details>
<summary>Click to expand the list</summary>

#### CreateControlHint(playerid, Float:x, Float:y, const description[], const control[], show = CH_SHOW_HINT, textAlignment = CH_TEXT_ALIGN_LEFT, selectable = 0)
> Create a hint
> * `Float:x` - X-Coordinate
> * `Float:y` - Y-Coordinate
> * `description[]` - Description text
> * `control[]` - Control button text
> * `show` - Show hint
> * `textAlignment` - Set the text alignment (CH_TEXT_ALIGN_LEFT or CH_TEXT_ALIGN_RIGHT)
> * `selectable` - Whether the hint is selectable

#### CreateControlHintBelow(playerid, Float:xOffset, Float:yOffset, const description[], const control[], show = CH_SHOW_HINT, textAlignment = CH_TEXT_ALIGN_LEFT, selectable = 0)
> Create a hint below the previous hint
> * `Float:xOffset` - X-Offset from the previous hint
> * `Float:yOffset` - Y-Offset from the previous hint
> * `description[]` - Description text
> * `control[]` - Control button text
> * `show` - Show hint
> * `textAlignment` - Set the text alignment (CH_TEXT_ALIGN_LEFT or CH_TEXT_ALIGN_RIGHT)
> * `selectable` - Whether the hint is selectable

#### CreateControlHintAbove(playerid, Float:xOffset, Float:yOffset, const description[], const control[], show = CH_SHOW_HINT, textAlignment = CH_TEXT_ALIGN_LEFT, selectable = 0)
> Create a hint above the previous hint
> * `Float:xOffset` - X-Offset from the previous hint
> * `Float:yOffset` - Y-Offset from the previous hint
> * `description[]` - Description text
> * `control[]` - Control button text
> * `show` - Show hint
> * `textAlignment` - Set the text alignment (CH_TEXT_ALIGN_LEFT or CH_TEXT_ALIGN_RIGHT)
> * `selectable` - Whether the hint is selectable

#### DestroyControlHint(playerid, &hintid)
> Destroy a control hint
> * `playerid` - The ID of the player
> * `hintid` - The ID of the hint
> * Note: `hintid` will be set to 0 after being destroyed

#### DestroyAllControlHints(playerid)
> Destroy all control hints for a player
> * `playerid` - The ID of the player

#### IsControlHintValid(playerid, hintid)
> Check if a control hint is valid
> * `playerid` - The ID of the player
> * `hintid` - The ID of the hint
> * Returns `true` if the hint is valid, `false` otherwise

#### ShowControlHint(playerid, hintid)
> Show a control hint
> * `playerid` - The ID of the player
> * `hintid` - The ID of the hint

#### HideControlHint(playerid, hintid)
> Hide a control hint
> * `playerid` - The ID of the player
> * `hintid` - The ID of the hint

#### IsControlHintVisible(playerid, hintid)
> Check if a control hint is visible
> * `playerid` - The ID of the player
> * `hintid` - The ID of the hint
> * Returns `true` if the hint is visible, `false` otherwise

#### HideAllControlHints(playerid, bool:remember = false)
> Hide all control hints for a player
> * `playerid` - The ID of the player
> * `remember` - Whether to remember the hidden state
> * Note: `remember` - if `true`, hints that were visible will be restored by `ShowAllControlHints`

#### ShowAllControlHints(playerid)
> Show all control hints for a player
> * `playerid` - The ID of the player

#### UpdateControlHintText(playerid, hintid, const description[], const control[] = "", show = CH_SHOW_HINT)
> Update the text of a control hint
> * `playerid` - The ID of the player
> * `hintid` - The ID of the hint
> * `description[]` - New description text
> * `control[]` - New control button text
> * `show` - Show or hide the hint after updating

#### SetControlHintAnchorX(playerid, hintid, Float:offset = 0.0)
> Sets the anchor X position to the hint's X, used as the base for CreateControlHintAbove/Below.
> * `playerid` - The ID of the player
> * `hintid` - The ID of the hint
> * `offset` - The X offset from the anchor point

#### SetControlHintAnchorY(playerid, hintid, Float:offset = 0.0)
> Sets the anchor Y position to the hint's Y, used as the base for CreateControlHintAbove/Below.
> * `playerid` - The ID of the player
> * `hintid` - The ID of the hint
> * `offset` - The Y offset from the anchor point

#### SetControlHintPosition(playerid, hintid, Float:x, Float:y, show = CH_SHOW_HINT)
> Set the position of a control hint
> * `playerid` - The ID of the player
> * `hintid` - The ID of the hint
> * `x` - The X position
> * `y` - The Y position
> * `show` - Show or hide the hint after setting the position

#### GetControlHintPosition(playerid, hintid, &Float:x, &Float:y, Float:xOffset = 0.0, Float:yOffset = 0.0)
> Get the position of a control hint
> * `playerid` - The ID of the player
> * `hintid` - The ID of the hint
> * `x` - The X position
> * `y` - The Y position
> * `xOffset` - The X offset from the anchor point
> * `yOffset` - The Y offset from the anchor point

#### StartControlHintAnimation(playerid, hintid, backgroundColor, Float:speed = 15.0)
> Start a control hint animation
> * `playerid` - The ID of the player
> * `hintid` - The ID of the hint
> * `backgroundColor` - The background color of the animation
> * `speed` - The speed of the animation
> * Calls `OnPlayerControlHintAnimationEnd` when the animation ends

#### StopControlHintAnimation(playerid, hintid)
> Stop a control hint animation
> * `playerid` - The ID of the player
> * `hintid` - The ID of the hint

#### IsControlHintAnimating(playerid, hintid)
> Check if a control hint is animating
> * `playerid` - The ID of the player
> * `hintid` - The ID of the hint
> * Returns `true` if the hint is animating, `false` otherwise

#### HighlightControlHintBackground(playerid, hintid, backgroundColor, timeout = 1000)
> Highlight the background of a control hint
> * `playerid` - The ID of the player
> * `hintid` - The ID of the hint
> * `backgroundColor` - The background color to highlight
> * `timeout` - The duration of the highlight in milliseconds

</details>


## Callbacks
<details>
<summary>Click to expand the list</summary>

#### public OnPlayerControlHintAnimationEnd(playerid, hintid)
> Called when a control hint animation ends
> * `playerid` - The ID of the player
> * `hintid` - The ID of the hint

#### public OnPlayerControlHintClicked(playerid, hintid)
> Called when a control hint is clicked
> * `playerid` - The ID of the player
> * `hintid` - The ID of the hint
</details>


## Definition
<details>
<summary>Click to expand the list</summary>

```pawn
#define CH_MAX_CONTROL_HINTS 32

#define CH_DESCRIPTION_LENGTH 128
#define CH_CONTROL_LENGTH 64

#define CH_LETTER_SIZE_X 0.1598
#define CH_LETTER_SIZE_Y 0.9199
#define CH_BACKGROUND_HEIGHT 11.5

#define CH_BACKGROUND_COLOR 0x1e1e1eFF
#define CH_FOREGROUND_COLOR 0x353535FF

#define CH_TEXT_COLOR 0xFFFFFFFF
#define CH_DESCRIPTION_COLOR 0xFFFFFFFF

#define CH_INVALID_ID 0

#define CH_TEXT_ALIGN_LEFT 		1
#define CH_TEXT_ALIGN_RIGHT 	3

#define CH_HIDE_HINT 	0
#define CH_SHOW_HINT 	1
```
</details
