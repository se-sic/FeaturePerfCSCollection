#include "fp_util/sleep.h"

using fp_util::busy_sleep_for_millisecs;

struct NormalGrid {
  virtual void init() {}

  virtual void doApply() {}

  virtual void doStuff() { busy_sleep_for_millisecs(1000); }
};

struct SpecialGrid {
  virtual void init() { busy_sleep_for_millisecs(1000); }

  virtual void doApply(int n) { busy_sleep_for_millisecs(1000); }

  virtual void doStuff(int n) {}
};

struct NormalSolver {
  template <class GridTy> void solve(GridTy &Grid) {
    busy_sleep_for_millisecs(1000);
    // Grid.doStuff();
  }
};

struct SpecialSolver {
  template <class GridTy, typename ApplyTy>
  void solveWithApply(GridTy &Grid, ApplyTy &Apply) {
    busy_sleep_for_millisecs(1000);
    Apply.apply(Grid, 5);
    busy_sleep_for_millisecs(1000);
  }
};

struct NormalApplier {
  template <typename GridTy> void apply(GridTy &Grid) {
    busy_sleep_for_millisecs(1000);
    // Grid.doApply();
  }
};

struct SpecialApplier {
  template <typename GridTy> void apply(GridTy &Grid, int n) {
    busy_sleep_for_millisecs(1000);
    Grid.doApply(n);
    busy_sleep_for_millisecs(1000);
  }

  void apply(SpecialGrid &Grid, int n) {
    busy_sleep_for_millisecs(1000);
    Grid.doStuff(n);
    busy_sleep_for_millisecs(1000);
  }
};

template <typename GridTy, typename ApplyTy, typename SolverTy>
void solveProblem(GridTy &Grid, ApplyTy &, SolverTy &Solver) {
  Solver.solve(Grid);
}

template <typename GridTy, typename ApplyTy>
void solveProblem(GridTy &Grid, ApplyTy &Apply, SpecialSolver &Solver) {
  Solver.solveWithApply(Grid, Apply);
}

template <typename GridTy, typename ApplyTy>
void applyToGrid(GridTy &Grid, ApplyTy &Apply) {
  Apply.apply(Grid);
}

template <typename GridTy>
void applyToGrid(GridTy &Grid, SpecialApplier &Apply) {
  Apply.apply(Grid, 5);
}

void run() {
  NormalGrid NGrid{};
  NormalApplier NApplier{};
  NormalSolver NSolver{};

  NGrid.init();

  applyToGrid(NGrid, NApplier);

  solveProblem(NGrid, NApplier, NSolver);

  SpecialGrid SGrid{};
  SpecialApplier SApplier{};
  SpecialSolver SSolver{};

  applyToGrid(SGrid, SApplier);

  solveProblem(SGrid, SApplier, SSolver);
}

int main(/* int argc, char *argv[] */) {
  run();

  return 0;
}
