import graphs, digraphs, csv
def gamesOK(games: set[tuple[str, str]]) -> bool:
    e = games.union((b, a) for (a, b) in games)
    v = {x for t in games for x in t}
    return all([set.union(*[graphs.N(v, e, i) | {i} for i in graphs.N(v, e, u)]) == v for u in v])
def potentialReferees(referee_csv_filename: str, player1: str, player2: str) -> set[str] | set[None]:
    with open(referee_csv_filename, newline="") as csvfile:
        refs_reader = csv.reader(csvfile, delimiter=",", quotechar="|")
        next(refs_reader)
        return {ref for ref, conflict_set in {row[0]: set(row) for row in refs_reader}.items() if not conflict_set & {player1, player2}}
def gameReferees(game_potential_referees: dict[tuple[str, str], set[str]]) -> dict[tuple[str, str], str] | None:
    a = set(game_potential_referees.keys())
    matches = {game: ref for (game, ref) in digraphs.maxMatching(a, set(ref for refs in game_potential_referees.values() for ref in refs), set((game, ref) for (game, refs) in game_potential_referees.items() for ref in refs)) if game in a}
    return matches if len(a) == len(matches) else None
def gameSchedule(assigned_referees: dict[tuple[str, str], str]) -> list[set[tuple[str, str, str]]]:
    v = {(*game, ref) for (game, ref) in assigned_referees.items()}
    k, c = graphs.minColouring(v, {(v1, v2) for v1 in v for v2 in v if v1 != v2 and set(v1) & set(v2)})
    return [{key for (key, value) in c.items() if value == i} for i in range(k)]
def ranking(games: set[tuple[str, str]]) -> list[str]: return digraphs.topOrdering({x for t in games for x in t}, games)