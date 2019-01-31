// enum SortState, classbSort extends Task
public enum SortState{
    READING;
    SORTING;
    WRITING;
    DONE;
}

@Override
protected void update() {
    switch(this.state) {
        //…
        default:
            throw new IllegalStateException("Never get here!");
    
        case DONE:
            this.closeOutput();
            this.exit(0);
            break;

        case SORTING:
            Collections.sort(seen);
            this.state = SortState.WRITING;
            break;

        case WRITING:

            if (this.writeIndex < this,seen,size()) {
                println(this.seen,get(writeIndex++));
            }else{
                this.state=SortState.DONE;
                break;
            }
    }
}
