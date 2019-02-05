package edu.smith.cs.csc262.coopsh.apps;

import edu.smith.cs.csc262.coopsh.InputLine;
import edu.smith.cs.csc262.coopsh.ShellEnvironment;
import edu.smith.cs.csc262.coopsh.Task;

import java.io.*;
import java.util.ArrayList;

public class SimpleGrep extends Task {

    /**
     * This is the state of this program; a BufferedReader.
     */
    private BufferedReader current = null;
    String rawPattern;
    /**
     * All tasks are created with a possibly empty list of string arguments!
     *
     * @param env
     * @param args - much like public static void main!
     */
    public SimpleGrep(ShellEnvironment env, String[] args) {

        super(env, args);
        if (args.length >2) {
            System.err.println("Can read only one file");
        }else if (args.length<2){
            System.err.println("Need 2 arguments");
        }


        File input = env.makeFile(args[1]);
        try {
            this.current = new BufferedReader(new FileReader(input));
        } catch (FileNotFoundException e) {
            caughtFatalException("Could not open file!", e);
        }

        this.rawPattern=this.getRawPattern(args[0]);

    }

    @Override
    protected void update() {

        String next;
        try {
            next = current.readLine();
        } catch (IOException e) {
            caughtFatalException("Reading file error!", e);
            return;
        }

        // Case 2A: We're done.
        if (next == null) {
            this.closeOutput();
            this.exit(0);;
            try {
                current.close();
            } catch (IOException e) {
                caughtFatalException("Could not close file!", e);
                return;
            }
            current = null;
        } else {
            // Case 2B: send this input along.
            if (next.contains(rawPattern))
                this.println(next);
        }


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
