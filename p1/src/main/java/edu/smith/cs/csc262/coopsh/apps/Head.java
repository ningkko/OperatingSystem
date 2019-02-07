package edu.smith.cs.csc262.coopsh.apps;

import edu.smith.cs.csc262.coopsh.ShellEnvironment;
import edu.smith.cs.csc262.coopsh.Task;

import java.io.*;

public class Head extends Task {

    /**
     * number of lines the user wants to print
     */
    int command;

    /**
     * Number of the current output line
     */
    int currentLineNum;

    /**
     * This is the state of this program; a BufferedReader.
     */
    private BufferedReader bufferedReader = null;

    /**
     * Prints the first few lines of given files
     * @param env
     * @param args
     */
    public Head(ShellEnvironment env, String[] args) {
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

    }

    @Override
    protected void update() {

        String nextLine;

        while(currentLineNum<=command){

            try {
                nextLine = bufferedReader.readLine();
            } catch (IOException e) {
                caughtFatalException("Reading file error!", e);
                this.exit(1);
                return;
            }

            if (nextLine == null) {
                try {
                    bufferedReader.close();
                } catch (IOException e) {
                    caughtFatalException("Could not close file!", e);
                    return;
                }
                bufferedReader = null;
                break;

            } else {
                // Case 2B: send this input along.
                this.println(nextLine);
                currentLineNum++;
            }
        }

        this.closeOutput();
        this.exit(0);
        return;

    }

}
