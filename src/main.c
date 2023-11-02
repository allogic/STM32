extern int _stack;

void reset_handler(void);
int main(void);

__attribute__((section(".isr_vector"))) void* g_vectors[] = {
	&_stack,
	reset_handler,
};

void reset_handler(void) {
	main();

	while (1);
}

int main(void) {
	return 0;
}
