## Encoding
- ASCII 
	- only english. From 0-127
	- byte, int8_t
- Browsers detect encodings using a provability table
- In English, character frequencies comes in "estlnr..." something like this.

- Unicode -> To support all languages
	- UCS32: 
		- 0-127 are english characters, 256+ are other words. 
		- Support emoji or other stuff.
		- Too expensive. => 000H for character "H". Four times than ASCII
	- USC-16:
		- Fewer supported characters but still most of them.

	- UTF32:
		- Unicode Text Format

- byte[] = just numbers -> InputStream( ,"UTF-8")
- String = meaning -> Reader
- bytes[] = "binary format"
	- .ppt
	- .doc(x)
	- .jpeg, .zip, .gz
	- .mr, .mp4, .mp3, .pdf, .class, .pyc, .o
- ASCII
	- .txt
	- .py (unicode)
	- .java (unicode)
	- .c
	- .data


- StringBuilder -> Inside is Char[] buffer
- StringBuffer -> Synchronized.

- line.decode("UTF-8") basically solves encoding problems