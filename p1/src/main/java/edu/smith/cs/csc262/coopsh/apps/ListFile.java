package edu.smith.cs.csc262.coopsh.apps;

import edu.smith.cs.csc262.coopsh.ShellEnvironment;
import edu.smith.cs.csc262.coopsh.Task;

import java.io.File;
import java.util.ArrayList;

public class ListFile extends Task {

    ArrayList<String> files, dirs,hiddens;
    /**
     * All tasks are created with a possibly empty list of string arguments!
     *
     * @param env
     * @param args - much like public static void main!
     */
    public ListFile(ShellEnvironment env, String[] args) {
        super(env, args);

        files=new ArrayList<>();
        dirs=new ArrayList<>();
        hiddens=new ArrayList<>();

    }

    @Override
    protected void update() {
        File folder = env.currentDirectory;
        File[] listOfFiles = folder.listFiles();


        for (int i = 0; i < listOfFiles.length; i++) {

            if (listOfFiles[i].isFile()) {
                files.add(listOfFiles[i].getName());
            }

            else if (listOfFiles[i].isDirectory()){
                dirs.add(listOfFiles[i].getName());

            }else if (listOfFiles[i].isHidden()){
                hiddens.add(listOfFiles[i].getName());
            }
        }

        if (files!=null){
            this.println("<-------- files -------->");
            for (String s:files){
                this.println(s);
            }

        }

        if (dirs!=null){
            this.println("<----- directories ----->");
            for (String s:dirs){
                this.println(s);
            }
        }

        if (hiddens!=null){
            this.println("<----- hidden files ----->");
            for (String s:hiddens){
                this.println(s);
            }
        }

        this.closeOutput();
        this.exit(0);
        return;
    }
}
