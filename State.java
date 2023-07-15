package missionariescannibals;

public class State {

    private int mis_num, can_num;
    private boolean side;
    private Double heuristic;
    private State parent;
    private int possibleChildrenCounter;

    public State(int mis_num, int can_num, boolean side, State parent) {
        this.mis_num = mis_num;
        this.can_num = can_num;
        this.side = side;
        this.parent = parent;
        this.possibleChildrenCounter = 0;
        this.heuristic = new Double((mis_num + can_num) / (double) 2);
    }
    
    public State getParent() {
        return this.parent;
    }
    
    public Double getHeuristic() {
        return this.heuristic;
    }
    
    public int getPossibleChildrenCounter() {
        return this.possibleChildrenCounter;
    }
    
    public void incrementCounter() {
        this.possibleChildrenCounter++;
    }
    
    public void decrementCounter() {
        this.possibleChildrenCounter--;
    }

    public int getMisNum() {
        return this.mis_num;
    }

    public int getCanNum() {
        return this.can_num;
    }

    public boolean getSide() {
        return this.side;
    }
    
    @Override
    public String toString() {
        String direction = this.side ? "Right" : "Left";
        return "Mis # = " + this.mis_num + ", Can # = " + 
                this.can_num + ", side = " + direction + ", h = " + this.heuristic + "\n";
    }
}
