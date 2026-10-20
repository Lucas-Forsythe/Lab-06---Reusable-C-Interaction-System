# Lab 07 - Event-Driven Interaction Extension

## Interaction Flow

The player looks at an interactable object.

The line-trace component detects the object when the player presses E.

The component checks whether the target implements `InteractableInterface`.

The component sends an interaction request to the target through the interface.

The target executes its assigned interaction behavior.

When the player interacts with an `InteractionSwitch`, the switch loops through its configured target array and activates each valid target.

Each door uses its existing opening behavior, including its configured activation delay.

## Independent Architecture Improvement

The independent extension is a reusable interaction switch with an editor-configurable target array. A single switch can activate multiple doors or other interactable actors without hard-coding each target into the switch logic. Designers can assign or change targets directly in the Unreal Editor. The switch checks target references before interacting with them and logs warnings for invalid targets.

This improves reusability and allows new interaction setups to be created without modifying the C++ source code.

# Lab 06 - Reusable Interaction System

## Interaction Flow

The player enters a trigger volume.

The detector receives the overlap event.

The detector calls SetDoorOpen(true) on its assigned target.

The target waits for its configured activation delay.

The door moves toward its open position.

When the player leaves the trigger, the detector requests that the door close.

## Independent Architecture Improvement

The independent extension is delayed door activation. Each door can have a different activation delay configured in the Editor. The target uses a timer to delay activation and cancels a pending opening when a close request is received.
