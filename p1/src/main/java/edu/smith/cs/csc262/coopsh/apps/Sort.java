package edu.smith.cs.csc262.coopsh.apps;

import edu.smith.cs.csc262.coopsh.ShellEnvironment;
import edu.smith.cs.csc262.coopsh.Task;

import java.io.*;
import java.util.ArrayList;
import java.util.Collections;

public class Sort extends Task {

    /**
     * to store the option
     */
    String command;
    /**
     * to store content read in from the filename or directory
     */
    ArrayList<String> content;

    /**
     * This is the state of this program; a BufferedReader.
     */
    private BufferedReader current = null;



    /**
     * All tasks are created with a possibly empty list of string arguments!
     *
     * @param env
     * @param args - much like public static void main!
     */
    public Sort(ShellEnvironment env, String[] args) {
        super(env, args);
        this.content=new ArrayList<>();

        if (args.length==1){
            File input = env.makeFile(args[0]);

            try {
                this.current = new BufferedReader(new FileReader(input));
            } catch (FileNotFoundException e) {
                caughtFatalException("Could not open file!", e);
            }


        }else if(args.length==2){
            command=args[0];
            File input=env.makeFile(args[1]);

            try {
                this.current = new BufferedReader(new FileReader(input));
            } catch (FileNotFoundException e) {
                caughtFatalException("Could not open file!", e);
            }
        }

        readFileinArray();

    }

    @Override
    protected void update() {

        if (args.length==1){
            defaultSort();
        }
        else {

            switch (command) {

                default:
                    this.println("No command found");

                case "-n":
                    this.defaultSort();

                case "-r":
                    this.reverseSort();

                case "-nr":
                    this.reverseSort();

                case "-rn":
                    this.reverseSort();
            }
        }

        if (content!=null){
            for (String s: content){
                this.println(s);
            }
        }

        this.closeOutput();
        this.exit(0);
        return;
    }

    private void defaultSort(){
        Collections.sort(content);
    }

    private void reverseSort(){
        Collections.sort(content);
        Collections.reverse(content);
    }

    private void readFileinArray(){

        String next;
        while (true){
            try {
                next = current.readLine();
            } catch (IOException e) {
                caughtFatalException("Reading file error!", e);
                break;
            }

            // Case 2A: We're done.
            if (next == null) {
                try {
                    current.close();
                } catch (IOException e) {
                    caughtFatalException("Could not close file!", e);
                    break;
                }
                current = null;
                break;

            } else {
                // Case 2B: send this input along.
                content.add(next);
            }
        }
    }
}
