CXXFLAGS=-O3 -lbenchmark -lpthread

all: ic-avl-array ic-avl-pointer ic-merge ic-fenwick ic-fenwick-perm

clean:
	rm -f ic-merge ic-avl-pointer ic-avl-array ic-fenwick ic-fenwick-perm

test: all
	./ic-merge        | tee output/ic-merge.out
	./ic-avl-pointer  | tee output/ic-avl-pointer.out
	./ic-avl-array    | tee output/ic-avl-array.out
	./ic-fenwick      | tee output/ic-fenwick.out
	./ic-fenwick-perm | tee output/ic-fenwick-perm.out

	./Transform < output/ic-merge.out        > data/ic-merge.dat
	./Transform < output/ic-avl-pointer.out  > data/ic-avl-pointer.dat
	./Transform < output/ic-avl-array.out    > data/ic-avl-array.dat
	./Transform < output/ic-fenwick.out      > data/ic-fenwick.dat
	./Transform < output/ic-fenwick-perm.out > data/ic-fenwick-perm.dat

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
