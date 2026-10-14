---
name: keyboard-flash-notifications
description: Build a direct, non-queued keyboard-light notification integration for the customized Drop SHIFT firmware. Use when a user asks to signal app, agent, CLI, workflow, or system events through this keyboard's flash interface.
---

# Keyboard Flash Notifications

Use this document when the user wants an application or agent to signal events
through the customized Drop SHIFT keyboard's underglow. Treat the notification
design below as a complete working example, not as a limit on other uses of the
flash interface.

## What the keyboard firmware accepts

The custom firmware handles a Raw HID command in
[`users/openbigger/openbigger.c`](users/openbigger/openbigger.c):

```
EA 12 21 <state> <red> <green> <blue>
```

- `<state>` `00`: turn the custom splash off. RGB bytes are ignored.
- Any nonzero `<state>`: turn the splash on using the following RGB bytes.
- RGB values are single bytes (`00`–`FF`).
- The firmware receives a fixed 32-byte Raw HID report and echoes the report
  back after applying the command.

The custom colored-RGB command requires the v1.4-or-newer firmware described
in [`readme.md`](readme.md). Do not change or reflash firmware merely to add a
host notification unless the user asks for firmware work.

## Host-side transport

Use a Raw HID client, not simulated keypresses, a vendor GUI, or a saved color
queue. On this keyboard, the target HID collection is:

| Field | Value |
| --- | --- |
| Vendor ID | `04D8` |
| Product ID | `EE65` |
| Usage page | `FF60` |
| Usage | `0061` |

With HIDAPI, enumerate that VID/PID pair and select the collection with the
usage page and usage above. For HIDAPI's report-ID API, write a 33-byte host
buffer: byte `0` is report ID `0`; bytes `1`–`7` are the seven command bytes;
the remainder is zero padding. Read the 32-byte response and verify that its
first seven bytes echo the command.

Do not assume every keyboard with the same VID/PID exposes the intended Raw
HID collection. If no matching collection is found, report that the compatible
keyboard or firmware is unavailable and do not fall back to another device.

## Minimal client contract

Provide a small executable or library with this contract:

```text
keyboard-flash --color RRGGBB
keyboard-flash --off
```

It should:

1. Validate exactly six hexadecimal color digits.
2. Open the matching Raw HID collection.
3. Send exactly one command immediately.
4. Verify the echo response before returning success.
5. Keep no color queue, daemon, or persisted "last color" state.

The last successful writer controls the physical light. This is intentional:
separate agents or applications do not need to coordinate with one another.

### Quick manual check

After installing or building a client, test only against the intended attached
keyboard:

```bash
keyboard-flash --color FF1493  # pink
keyboard-flash --off
```

If either command fails, surface the error rather than pretending a
notification was delivered. Do not send repeated test flashes without a user
request.

## Reference notification design: Codex or other agents

Use this pattern when the user asks for an attention system similar to the
Codex example. It is an example policy; confirm colors and triggering events
when the user specifies a different meaning.

| Event | Signal |
| --- | --- |
| Agent genuinely cannot continue without the user's answer or action | Send pink `FF1493` immediately, then repeat every 5 seconds while that *same* agent remains waiting. |
| The user answers that waiting agent, or it resumes work by itself | Stop only that agent's reminder loop; send `--off` only when it is clearing that agent's actual waiting state. |
| Agent completes a task | Read the live remaining allowance, map it to the agreed completion color, then send it once. |
| A new unrelated agent turn begins | Do not send `--off`; it could erase another agent's just-completed signal. |

For the completion-color example used in this setup:

| Remaining allowance | Color |
| --- | --- |
| >80% | blue `0052FF` |
| 60–80% | green `00FF48` |
| 40–59% | yellow `FFA500` |
| 20–39% | orange `FF5000` |
| <20% | red `C80A0A` |

### State model

Keep only the smallest per-agent state necessary to stop that agent's own
repeating reminder, for example a temporary file keyed by session ID containing
a random token. The loop checks that its token still exists before each send.
Deleting or replacing the token makes that loop exit safely.

Do **not** use shared global state to decide whether the keyboard is allowed to
flash. A completion signal from agent B may temporarily replace agent A's pink
signal; A's next five-second reminder may replace it again. This is desirable:
the human can choose which agent to inspect.

Avoid an unconditional `--off` on generic startup, a new prompt, or a new
conversation. Those events may belong to a different agent than the light that
is currently visible.

## Integrating with an agent runtime

1. First identify the runtime's actual lifecycle events and whether its hooks
   run locally with access to the Raw HID client. Do not assume a hook name or
   plugin feature works across CLI and desktop versions.
2. Bind the waiting reminder to events that truly require user input or
   approval. Cancel it when the same task resumes, is interrupted, or ends.
3. Bind the completion signal to the runtime's final completion event. Query
   any usage value at that time; do not reuse a cached allowance.
4. Make every flash command fire-and-forget from the caller's perspective:
   one direct HID write, no retry queue, no replay after reconnect.
5. Log diagnostic metadata only if requested. Never log sensitive agent
   prompts, credentials, or full conversation contents merely to explain a
   light event.

Some runtimes may emit an approval-related event even when an internal review
later continues automatically. Treat a persistent pink reminder as a
correctness bug: the system should cancel its own reminder as soon as the
originating task demonstrably resumes.

## Scope and safety

- Ask before installing dependencies, changing global agent configuration,
  modifying firmware, or flashing the keyboard.
- Preserve unrelated user changes and existing notification systems until the
  user explicitly asks to replace them.
- Keep hardware writes narrowly scoped to the matched Raw HID collection.
- This document supplies a reusable example. Users may assign different colors
  or automate entirely different events through the same interface.
