package missionariescannibals;

public class Rules {

    private int maxCan, maxMis;
    private int ml_count, cl_count, mr_count, cr_count;

    public Rules(int ml_count, int cl_count, int mr_count, int cr_count) {
        this.maxCan = cl_count + cr_count;
        this.maxMis = ml_count + mr_count;
        this.ml_count = ml_count;
        this.cl_count = cl_count;
        this.mr_count = mr_count;
        this.cr_count = cr_count;
    }

    public boolean isValidMove(State s) {
        if ((s.getCanNum() >= 0 && s.getCanNum() <= maxCan) && (s.getMisNum() >= 0 && s.getMisNum() <= maxMis)) {
            if((s.getCanNum() > s.getMisNum() && s.getMisNum() != 0) || (maxCan - s.getCanNum() > maxMis - s.getMisNum() && s.getMisNum() != maxMis)) {
                return false;
            } else {
                return true;
            }
        }
        return false;
    }

    public boolean isGoal(State s) {
        return s.getCanNum() + s.getMisNum() == 0;      // If both zero, then it is the goal
    }
}
