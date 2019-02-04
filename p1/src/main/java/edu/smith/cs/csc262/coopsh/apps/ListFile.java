package edu.smith.cs.csc262.coopsh.apps;

import edu.smith.cs.csc262.coopsh.ShellEnvironment;
import edu.smith.cs.csc262.coopsh.Task;

import java.io.File;

public class ListFile extends Task {
    /**
     * All tasks are created with a possibly empty list of string arguments!
     *
     * @param env
     * @param args - much like public static void main!
     */
    public ListFile(ShellEnvironment env, String[] args) {
        super(env, args);
    }

    @Override
    protected void update() {
        File folder = env.currentDirectory;
        File[] listOfFiles = folder.listFiles();

        for (int i = 0; i < listOfFiles.length; i++) {
            if (listOfFiles[i].isFile()) {
                this.println(listOfFiles[i].getName());
            }
        }
    }
}
