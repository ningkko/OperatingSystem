package edu.smith.cs.csc262.coopsh.apps;

import edu.smith.cs.csc262.coopsh.InputLine;
import edu.smith.cs.csc262.coopsh.ShellEnvironment;
import edu.smith.cs.csc262.coopsh.Task;

public class WordCount extends Task {
	int wordCount = 0;
	int lineCount=0;
	int byteCount=0;


	public WordCount(ShellEnvironment env, String[] args) {
		super(env, args);
	}

	@Override
	protected void update() {

		String command;
		InputLine line = this.input.poll();
		if (line == null) {
			// still waiting for more...
			return;
		}

		for(int i=0; i<args.length;i++){
			command=args[i];
			if (command.equals("-w")){
				this.findWords(line);
			}
			if(command.equals("-l")){
				this.findLine(line);
			}
			if(command.equals("-c")){
				this.findByte(line);
			}
		}

	}


	private void findWords(InputLine line){

		// only output and print when we've seen the whole file!
		if (line.isEndOfFile()) {
			this.println(wordCount);
			this.closeOutput();
			this.exit(0);
			return;

		}
		wordCount += line.get().split("\\s+").length;
	}

	private void findLine(InputLine line){

		// only output and print when we've seen the whole file!
		if (line.isEndOfFile()) {
			this.println(lineCount);
			this.closeOutput();
			this.exit(0);
			return;

		}
		lineCount++;
	}

	private void findByte(InputLine line){

		// only output and print when we've seen the whole file!
		if (line.isEndOfFile()) {
			this.println(byteCount);
			this.closeOutput();
			this.exit(0);
			return;

		}
		byteCount+=line.toString().getBytes().length;
	}

}
