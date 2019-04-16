## RAID ::= Redundant Arrays of Independent Disks
## JBOD ::= Just A Bunch of Disks
## striping (RAID[0] RAID has different numbers represening these stuff) -> put different pieces of odes onto different disks. 
- For speed. 
- Trade off: reliability
- If one of the buses break down, then the whole code will break.
- Usually used by people developing games (for speed). Also Google Index

## Mirroring
- For reliability
- Have a entire copy of the whole disk
- To decrease the probalbility of disk failure
- RAID controller. take care of all copies of the disk. When someone writes something, it writes the data onto all copies etc.

## Parity
- For reliability
- ECC ::= Error-Correcting Codes
- Correcting code for one missing bit.
- Counts the total eveness (0 for even and 1 for odd).
- 0000 (parity = 0), 0001 (1), 0010 (1), 0100 (1), 1000 (1), 0011 (0)...
- If missing 1 bit: 0?00 (parity = 0), then we can restore that ?=0.

