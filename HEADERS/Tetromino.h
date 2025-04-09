#ifndef TETROMINO_H
#define TETROMINO_H

#include "Library.h"
#include "TetrominoParent.h"

class LShape : public TetrominoParent {
public:
    LShape(int row, int col, int angle = 0) : TetrominoParent(row, col, angle) {
        shape = {
            {
                {1, 0},
                {1, 0},
                {1, 1}
            },
            {
                {1, 1, 1},
                {1, 0, 0}
            },
            {
                {1, 1},
                {0, 1},
                {0, 1}
            },
            {
                {0, 0, 1},
                {1, 1, 1}
            }
        };
    }
};

class JShape : public TetrominoParent {
public:
    JShape(int row, int col, int angle = 0) : TetrominoParent(row, col, angle) {
        shape = {
            {
                {0, 2},
                {0, 2},
                {2, 2}
            },
            {
                {2, 0, 0},
                {2, 2, 2}
            },
            {
                {2, 2},
                {2, 0},
                {2, 0}
            },
            {
                {2, 2, 2},
                {0, 0, 2}
            }
        };
    }
};

class OShape : public TetrominoParent {
public:
    OShape(int row, int col, int angle = 0) : TetrominoParent(row, col, angle) {
        shape = {
            {
                {3, 3},
                {3, 3}
            },
            {
                {3, 3},
                {3, 3}
            },
            {
                {3, 3},
                {3, 3}
            },
            {
                {3, 3},
                {3, 3}
            }
        };
    }
};

class TShape : public TetrominoParent {
public:
    TShape(int row, int col, int angle = 0) : TetrominoParent(row, col, angle) {
        shape = {
            {
                {0, 4, 0},
                {4, 4, 4}
            },
            {
                {4, 0},
                {4, 4},
                {4, 0}
            },
            {
                {4, 4, 4},
                {0, 4, 0}
            },
            {
                {0, 4},
                {4, 4},
                {0, 4}
            }
        };
    }
};

class SShape : public TetrominoParent {
public:
    SShape(int row, int col, int angle = 0) : TetrominoParent(row, col, angle) {
        shape = {
            {
                {0, 5, 5},
                {5, 5, 0}
            },
            {
                {5, 0},
                {5, 5},
                {0, 5}
            },
            {
                {0, 5, 5},
                {5, 5, 0}
            },
            {
                {5, 0},
                {5, 5},
                {0, 5}
            }
        };
    }
};

class ZShape : public TetrominoParent {
public:
    ZShape(int row, int col, int angle = 0) : TetrominoParent(row, col, angle) {
        shape = {
            {
                {6, 6, 0},
                {0, 6, 6}
            },
            {
                {0, 6},
                {6, 6},
                {6, 0}
            },
            {
                {6, 6, 0},
                {0, 6, 6}
            },
            {
                {0, 6},
                {6, 6},
                {6, 0}
            }
        };
    }
};

class IShape : public TetrominoParent {
public:
    IShape(int row, int col, int angle = 0) : TetrominoParent(row, col, angle) {
        shape = {
            {
                {7},
                {7},
                {7},
                {7}
            },
            {
                {7, 7, 7, 7}
            },
            {
                {7},
                {7},
                {7},
                {7}
            },
            {
                {7, 7, 7, 7}
            }
        };
    }
};

#endif
