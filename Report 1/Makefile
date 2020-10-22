CXXFLAGS=-O3 -lbenchmark -lpthread

all: ic-avl-array ic-avl-pointer ic-merge ic-fenwick ic-fenwick-perm

clean:
	rm -f ic-merge ic-avl-pointer ic-avl-array ic-fenwick ic-fenwick-perm

test: all
	./ic-merge        | tee results/ic-merge.out
	./ic-avl-pointer  | tee results/ic-avl-pointer.out
	./ic-avl-array    | tee results/ic-avl-array.out
	./ic-fenwick      | tee results/ic-fenwick.out
	./ic-fenwick-perm | tee results/ic-fenwick-perm.out

	./Transform < results/ic-merge.out        > results/ic-merge.dat
	./Transform < results/ic-avl-pointer.out  > results/ic-avl-pointer.dat
	./Transform < results/ic-avl-array.out    > results/ic-avl-array.dat
	./Transform < results/ic-fenwick.out      > results/ic-fenwick.dat
	./Transform < results/ic-fenwick-perm.out > results/ic-fenwick-perm.dat

ic-merge: InversionCount.hpp InversionCountMergeSort.cpp Benchmark.cpp
	$(CXX) $^ -o $@ $(CXXFLAGS)
ic-avl-pointer: InversionCount.hpp InversionCountAVLPointers.cpp Benchmark.cpp
	$(CXX) $^ -o $@ $(CXXFLAGS)
ic-avl-array: InversionCount.hpp InversionCountAVLArray.cpp Benchmark.cpp
	$(CXX) $^ -o $@ $(CXXFLAGS)
ic-fenwick: InversionCount.hpp InversionCountFenwick.cpp Benchmark.cpp
	$(CXX) $^ -o $@ $(CXXFLAGS)
ic-fenwick-perm: InversionCount.hpp InversionCountFenwickPermutation.cpp Benchmark.cpp
	$(CXX) $^ -o $@ $(CXXFLAGS)
