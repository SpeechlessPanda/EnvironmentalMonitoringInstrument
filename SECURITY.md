# Security Policy

This is a student lab device: no cloud backend, no accounts, no stored
credentials in firmware.

## Please do not file public issues that include

- Student ID numbers, phone numbers, QQ, or mailing addresses
- Debugger serial numbers, local disk paths, or Keil license names
- Bluetooth module MAC / pairing PIN / AT command dumps from a personal unit
- Course reports marked internal-use by the university

## Hardware notes

- HC-05 default pairing PIN is commonly `1234`. Change it with AT commands
  on your own module; do not commit a custom PIN.
- The web dashboard filters by advertised name `HC-05` and uses the public
  BLE UART UUIDs `FFE0` / `FFE1`. It does not embed a device MAC.
- Debug UART0 is 9600 8N1 with no authentication. Treat it as a local console.

## Reporting

Open a GitHub issue without attaching personal course paperwork, or email
the repository owner. We will strip secrets from git history if any slip
through a commit.
