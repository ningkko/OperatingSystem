package edu.smith.cs.csc262.coopsh.apps;

import edu.smith.cs.csc262.coopsh.ShellEnvironment;
import edu.smith.cs.csc262.coopsh.Task;

import java.util.ArrayList;
import java.util.Collections;

public class Sort extends Task {
    String command;
    ArrayList<String> filenames;
    /**
     * All tasks are created with a possibly empty list of string arguments!
     *
     * @param env
     * @param args - much like public static void main!
     */
    public Sort(ShellEnvironment env, String[] args) {
        super(env, args);
        this.command=args[0];
    }

    @Override
    protected void update() {
        switch (command){

            default:
                this.defaultSort();
            case "r":

        }
    }

    private void defaultSort(){

        //Collections.sort();

    }

    private void r(){

    }

    private void n(){

    }


    private void getFilenames(){

        if (this.args[0].substring(0,0).equals("-")){
            
            //filenames.add()
        }
    }
}
