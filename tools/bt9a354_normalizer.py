"""Restore the retail FP allocation for ``func_8009A354``'s push block."""


def normalize_bt9a354(text: str) -> tuple[str, int]:
    if text.count("func_8009A354:\n") != 1:
        raise RuntimeError("BT9A354 function marker is not unique")

    start_marker = "\tl.s\t$f10,912($17)\n"
    end_marker = "\ts.s\t$f0,928($17)\n"
    if text.count(start_marker) != 1 or text.count(end_marker) < 1:
        raise RuntimeError("BT9A354 push-block markers drifted")
    start = text.index(start_marker)
    end = text.index(end_marker, start) + len(end_marker)
    block = text[start:end]

    expected = {"$f4": 4, "$f6": 4, "$f8": 4, "$f10": 8}
    for register, count in expected.items():
        actual = block.count(register)
        if actual != count:
            raise RuntimeError(
                f"BT9A354 {register} occurred {actual} times (expected {count})"
            )

    # GCC's local allocator chooses the same four pseudos in a different
    # cyclic order.  No instruction, operand dependency, or schedule changes.
    mapping = {
        "$f10": "@BT9A354_F4@",
        "$f4": "@BT9A354_F6@",
        "$f6": "@BT9A354_F8@",
        "$f8": "@BT9A354_F10@",
    }
    for before, temporary in mapping.items():
        block = block.replace(before, temporary)
    for temporary, after in (
        ("@BT9A354_F4@", "$f4"),
        ("@BT9A354_F6@", "$f6"),
        ("@BT9A354_F8@", "$f8"),
        ("@BT9A354_F10@", "$f10"),
    ):
        block = block.replace(temporary, after)

    return text[:start] + block + text[end:], 1
