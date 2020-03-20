SCC_Tarjan(G, value)
	visited ← 0
	L ← 0
	for each vertex u ∈ V[G]
		do d[u] ← ∞
	for each vertex u ∈ V[G]
		do if d[u] = ∞
			then Tarjan_Visit(u, null, value)


Tarjan_Visit(u, null, value)
	d[u] ← low[u] ← visited
	visited ← visited + 1
	Push(L,u)
	for each v ∈ Adj[u]
		value[u] ← max(value[u], value[v])
		do if (d[v] = ∞ || v ∈ L)
			then if d[v] = ∞
				then Tarjan_Visit(v, u, value)
			low[u] ← min(low[u],low[v])
	
	Scc ← 0
	if d[u] = low[u]
		then repeat
			v ← Pop(L)
			Push(Scc, v)
			until u = v

		#Update the value in this Scc to
		#the max of it modes's members
		value[Scc] ← -1
		for each s ∈ Scc
			value[Scc] = max(value[Scc], value[s])

		#Update the value of the parent if 
		#it is bigger than the curr value
		if parent != null
			value[parent] ← max(value[parent], value[Scc])

