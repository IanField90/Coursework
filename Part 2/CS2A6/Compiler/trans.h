enum CLASSIFICATION { NUMBER, INFINITY, NEG_INFINITY, NULLITY };

struct TransrealNumber {
	enum CLASSIFICATION type;
	int value;
};

struct TransrealNumber evaluate(struct TransrealNumber *a, struct TransrealNumber *b, char opp);