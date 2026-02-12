# zig - eratosthenes såll

kompilerad med:
`zig build-exe sieve.zig -O ReleaseFast -target native`

`usr/bin/time -v ./sieve` gav mig 3,78 sek som bäst. Imponerande :D

För 10 000 000 000 tog det 44,72 sekunder och tog 610840 kB ram, ca 600 MB.

zig version: 0.16.0-dev.2510+bcb5218a2