package edu.smith.cs.csc262.coopsh.apps;

import edu.smith.cs.csc262.coopsh.ShellEnvironment;
import edu.smith.cs.csc262.coopsh.Task;

import java.io.*;

public class Head extends Task {

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

        if (args.length > 2) {
            System.err.println("Can only read one file.");
        }
        else if(args.length==1){
            File input = env.makeFile(args[0]);
            createBufferedReader(input);
        }else{
            File input = env.makeFile(args[1]);
            createBufferedReader(input);
        }

    }

    @Override
    protected void update() {

        if (args.length==1){
           new Cat(env,args);
        }else{

            int stopLineNum=1;
            try{
                stopLineNum=Integer.parseInt(args[0]);
            }catch (Exception e){
                System.err.println("Wrong type of line number passed");
            }
            int currentLineNum=1;
            String nextLine;

            while(currentLineNum<=stopLineNum){

                try {
                    nextLine = bufferedReader.readLine();
                } catch (IOException e) {
                    caughtFatalException("Reading file error!", e);
                    return;
                }

                if (nextLine == null) {
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
                    // Case 2B: send this input along.
                    this.println(nextLine);
                    currentLineNum++;
                }
            }

        }

    }

    private void createBufferedReader(File input){
        try {
            this.bufferedReader = new BufferedReader(new FileReader(input));
        } catch (FileNotFoundException e) {
            caughtFatalException("Could not open file!", e);
        }
    }



}
