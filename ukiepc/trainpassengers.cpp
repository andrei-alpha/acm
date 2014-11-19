#include <cstdio>

int main() {
	int cap, n, cnt = 0;
	scanf("%d%d", &cap, &n);

	int out, in, wait;
	bool ok = true;
	for (int i = 1; ok && i <= n; ++i) {
		scanf("%d%d%d", &out, &in, &wait);

		if (out > cnt)
			ok = false;
		cnt -= out;
		if (in + cnt > cap)
			ok = false;
		cnt += in;
		if (cnt != cap && wait)
			ok = false;
		if (i == n && wait)
			ok = false;
	}
	if (cnt)
		ok = false;

	if (ok)
		printf("possible\n");
	else
		printf("impossible\n");
	return 0;
}