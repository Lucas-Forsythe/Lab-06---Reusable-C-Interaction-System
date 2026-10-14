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
