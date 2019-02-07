package edu.smith.cs.csc262.coopsh.apps;

import edu.smith.cs.csc262.coopsh.ShellEnvironment;
import edu.smith.cs.csc262.coopsh.Task;

import java.io.*;
import java.util.ArrayList;
import java.util.Collections;

public class Tail extends Task {

    /**
     * number of lines the user wants to print
     */
    int command;

    /**
     * Number of the current output line
     */
    int currentLineNum;


    /**
     * to store content read in from the filename or directory
     */
    ArrayList<String> content;

    /**
     * This is the state of this program; a BufferedReader.
     */
    private BufferedReader bufferedReader = null;

    /**
     * Prints the first few lines of given files
     * @param env
     * @param args
     */
    public Tail(ShellEnvironment env, String[] args) {
        super(env, args);

        if (args.length != 2) {
            System.err.println("2 input arguments expected.");
            this.exit(1);
            return;
        }

        try{
            command=Integer.parseInt(args[0]);
        }catch (Exception err){
            caughtFatalException("First argument -> integer expected",err);
        }

        currentLineNum=1;

        File input = env.makeFile(args[1]);
        try {
            this.bufferedReader = new BufferedReader(new FileReader(input));
        } catch (FileNotFoundException e) {
            caughtFatalException("Could not open file!", e);
        }

        content=new ArrayList<>();
        readFileinArray(bufferedReader);
        Collections.reverse(content);
    }

    @Override
    protected void update() {


        while(currentLineNum<=command){

            if (currentLineNum>content.size()) {

                break;

            } else {
                // Case 2B: send this input along.
                this.println(content.get(currentLineNum-1));
                currentLineNum++;
            }
        }

        this.closeOutput();
        this.exit(0);
        return;

    }

    private void readFileinArray(BufferedReader current){

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
