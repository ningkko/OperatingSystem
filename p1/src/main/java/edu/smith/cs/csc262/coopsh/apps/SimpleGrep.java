package edu.smith.cs.csc262.coopsh.apps;

import edu.smith.cs.csc262.coopsh.InputLine;
import edu.smith.cs.csc262.coopsh.ShellEnvironment;
import edu.smith.cs.csc262.coopsh.Task;

import java.util.ArrayList;

public class SimpleGrep extends Task {

    String rawPattern;
    /**
     * All tasks are created with a possibly empty list of string arguments!
     *
     * @param env
     * @param args - much like public static void main!
     */
    public SimpleGrep(ShellEnvironment env, String[] args) {

        super(env, args);
        // get pattern without quotes
        this.rawPattern=this.getRawPattern(args[0]);

    }

    @Override
    protected void update() {

        ArrayList<String> linesContainingPattern = new ArrayList<>();

        InputLine line = this.input.poll();

        // only output and print when we've seen the whole file!
        if (line.isEndOfFile()) {
            this.println(linesContainingPattern);
            this.closeOutput();
            this.exit(0);
            return;

        }

        if (line.toString().contains(this.rawPattern))
            linesContainingPattern.add(line.toString());


    }

    private String getRawPattern(String pattern){

        if (pattern.substring(0,1).equals("\"")
                || pattern.substring(0,1).equals("\'")){
            // get rid of the quotes
            return pattern.substring(1,pattern.length()-2);
        }

        return pattern;

    }
}
