package edu.smith.cs.csc262.coopsh.apps;

import edu.smith.cs.csc262.coopsh.ShellEnvironment;
import edu.smith.cs.csc262.coopsh.Task;

public class Echo extends Task {
    /**
     * All tasks are created with a possibly empty list of string arguments!
     *
     * @param env
     * @param args - much like public static void main!
     */
    public Echo(ShellEnvironment env, String[] args) {
        super(env, args);
    }

    @Override
    protected void update() {

        String arg=String.join(" ",args);

        this.println(arg);

    }
}
