package edu.smith.cs.csc262.coopsh.apps;

import edu.smith.cs.csc262.coopsh.ShellEnvironment;
import edu.smith.cs.csc262.coopsh.Task;

import java.io.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class RegexGrep extends Task {

    /**
     * what can i say
     */
    BufferedReader bufferedReader;

    /**
     * regex pattern
     */
    Pattern pattern;
    /**
     * regex matcher
     */
    Matcher matcher;

    /**
     * All tasks are created with a possibly empty list of string arguments!
     *
     * @param env
     * @param args - much like public static void main!
     */
    public RegexGrep(ShellEnvironment env, String[] args) {
        super(env, args);

        if (args.length !=2) {
            System.err.println("Exactly 2 arguments expected");
            this.closeOutput();
            this.exit(1);
        }

        File input = env.makeFile(args[1]);
        try {
            this.bufferedReader = new BufferedReader(new FileReader(input));
        } catch (FileNotFoundException e) {
            caughtFatalException("Could not open file!", e);
        }

        this.pattern=Pattern.compile(args[0]);
    }

    @Override
    protected void update() {
        String next;
        try {
            next = bufferedReader.readLine();
        } catch (IOException e) {
            caughtFatalException("Reading file error!", e);
            return;
        }

        // Case 2A: We're done.
        if (next == null) {
            this.closeOutput();
            this.exit(0);;
            try {
                bufferedReader.close();
            } catch (IOException e) {
                caughtFatalException("Could not close file!", e);
                return;
            }
            bufferedReader = null;
        } else {

            matcher=pattern.matcher(next);

            // Case 2B: send this input along.
            if (matcher.find()) {
                this.println(next);
            }
        }

    }
}
