package edu.smith.cs.csc262.coopsh.apps;

import edu.smith.cs.csc262.coopsh.ShellEnvironment;
import edu.smith.cs.csc262.coopsh.Task;

public class SetVar extends Task {

    String variableName;
    /**
     * Simply prints the value which the variable is set to
     *
     * @param env
     * @param args - much like public static void main!
     */
    public SetVar(ShellEnvironment env, String[] args, String variableName) {
        super(env, args);
        this.variableName=variableName;
    }

    @Override
    protected void update() {
        this.println(env.getVariable(variableName));
        this.closeOutput();
        this.exit(0);
    }
}