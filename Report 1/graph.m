load ic-merge.dat
load ic-avl-pointer.dat
load ic-avl-array.dat
load ic-fenwick.dat
load ic-fenwick-perm.dat


N=1024
plot(ic_merge(1:N,1), ic_merge(1:N,2), ";merge;",
     ic_avl_pointer(1:N,1), ic_avl_pointer(1:N,2), ";avl-pointer;",
     ic_avl_array(1:N,1), ic_avl_array(1:N,2), ";avl-array;",
     ic_fenwick(1:N,1), ic_fenwick(1:N,2), ";fenwick;",
     ic_fenwick_perm(1:N,1), ic_fenwick_perm(1:N,2), ";fenwick-perm;")
xlabel ("Dimension");
ylabel ("Time (ns)");
legend ("location", "northwest")

N=1151
plot(ic_merge(1:N,1), ic_merge(1:N,2)/1000000, ".-;merge;", "markersize", 2,
     ic_avl_pointer(1:N,1), ic_avl_pointer(1:N,2)/1000000, ".-;avl-pointer;", "markersize", 2,
     ic_avl_array(1:N,1), ic_avl_array(1:N,2)/1000000, ".-;avl-array;", "markersize", 2,
     ic_fenwick(1:N,1), ic_fenwick(1:N,2)/1000000, ".-;fenwick;", "markersize", 2,
     ic_fenwick_perm(1:N,1), ic_fenwick_perm(1:N,2)/1000000, ".-;fenwick-perm;", "markersize", 2)
xlabel ("Dimension");
ylabel ("Time (ms)");
legend ("location", "northwest")

N=1160
plot(ic_merge(1:N,1)/1000, ic_merge(1:N,2)/1000000000, ".-;merge;", "markersize", 8,
     ic_avl_pointer(1:N,1)/1000, ic_avl_pointer(1:N,2)/1000000000, ".-;avl-pointer;", "markersize", 8,
     ic_avl_array(1:N,1)/1000, ic_avl_array(1:N,2)/1000000000, ".-;avl-array;", "markersize", 8,
     ic_fenwick(1:N,1)/1000, ic_fenwick(1:N,2)/1000000000, ".-;fenwick;", "markersize", 8,
     ic_fenwick_perm(1:N,1)/1000, ic_fenwick_perm(1:N,2)/1000000000, ".-;fenwick-perm;", "markersize", 8)
xlabel ("Dimension (thousands)");
ylabel ("Time (s)");
legend ("location", "northwest")

N=20
plot(ic_merge(1:N,1), ic_merge(1:N,2)/1000000000, ".-;merge;", "markersize", 10,
     ic_fenwick(1:N,1), ic_fenwick(1:N,2)/1000000000, ".-;fenwick;", "markersize", 10,
     ic_fenwick_perm(1:N,1), ic_fenwick_perm(1:N,2)/1000000000, ".-;fenwick-perm;", "markersize", 10)
xlabel ("Dimension");
ylabel ("Time (s)");
legend ("location", "northwest")
