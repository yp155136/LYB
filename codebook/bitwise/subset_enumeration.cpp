int subset_enumeration(int s) {
    for (int now = s; now > 0; now = (now - 1) & s) {
        cout << now << ' ';
    }
	cout << "0\n";
}
