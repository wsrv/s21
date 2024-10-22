import functional_purse

def split_booty(*purses: dict[str, int]) -> tuple[dict[str, int], dict[str, int], dict[str, int]]:
    total_gold = sum(purse.get("gold_ingots", 0) for purse in purses)
    avg_gold = total_gold // 3
    remainder = total_gold % 3

    purse1 = (functional_purse.empty({}))
    purse2 = (functional_purse.empty({}))
    purse3 = (functional_purse.empty({}))

    for _ in range(avg_gold):
        purse1 = functional_purse.add_ingot(purse1)
    if remainder > 0:
                purse1 = functional_purse.add_ingot(purse1)
    for _ in range(avg_gold):
        purse2 = functional_purse.add_ingot(purse2)
    if remainder > 1:
        purse2 = functional_purse.add_ingot(purse2)
    for _ in range(avg_gold):
        purse3 = functional_purse.add_ingot(purse3)

    return purse1, purse2, purse3