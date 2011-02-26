enum CLASSIFICATION { NUMBER, INFINITY, NEG_INFINITY, NULLITY };

struct TransrealNumber {
	enum CLASSIFICATION type;
	int value;
};

struct TransrealNumber evaluate(struct TransrealNumber *a, char opp, struct TransrealNumber *b);

void display(struct TransrealNumber res);