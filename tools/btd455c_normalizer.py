"""Restore retail allocation and scheduling for ``func_800D455C``."""


def _replace_once(text: str, before: str, after: str, description: str) -> str:
    count = text.count(before)
    if count != 1:
        raise RuntimeError(
            f"BTD455C {description} pattern occurred {count} times (expected 1)"
        )
    return text.replace(before, after, 1)


def normalize_btd455c(text: str) -> tuple[str, int]:
    if text.count("func_800D455C:\n") != 1:
        raise RuntimeError("BTD455C function marker is not unique")

    function_start = text.index("func_800D455C:\n")
    allocation_end_marker = "\tli\t$18,0x00000005\t\t# 5\n"
    if text.count(allocation_end_marker) != 1:
        raise RuntimeError("BTD455C allocation end marker drifted")
    allocation_end = text.index(allocation_end_marker, function_start)
    prefix = text[function_start:allocation_end]

    # GCC assigned the three long-lived values to a cyclically different set
    # of saved registers.  The values and their live ranges are otherwise
    # identical to retail.
    for register, expected in (("$16", 8), ("$18", 7), ("$19", 7)):
        actual = prefix.count(register)
        if actual != expected:
            raise RuntimeError(
                f"BTD455C {register} allocation count was {actual} (expected {expected})"
            )
    for before, temporary in (
        ("$19", "@BTD455C_S2@"),
        ("$18", "@BTD455C_S0@"),
        ("$16", "@BTD455C_S3@"),
    ):
        prefix = prefix.replace(before, temporary)
    for temporary, after in (
        ("@BTD455C_S2@", "$18"),
        ("@BTD455C_S0@", "$16"),
        ("@BTD455C_S3@", "$19"),
    ):
        prefix = prefix.replace(temporary, after)
    text = text[:function_start] + prefix + text[allocation_end:]

    for before, after, description in (
        ("\tsw\t$18,204($sp)\n", "\tsw\t$18,200($sp)\n", "s2 save slot"),
        ("\tsw\t$16,200($sp)\n", "\tsw\t$16,192($sp)\n", "s0 save slot"),
        ("\tsw\t$19,192($sp)\n", "\tsw\t$19,204($sp)\n", "s3 save slot"),
    ):
        text = _replace_once(text, before, after, description)

    setup_before = (
        "\tmove\t$7,$19\n"
        "\tnor\t$2,$0,$19\n"
        "\tsra\t$2,$2,31\n"
        "\tand\t$19,$19,$2\n"
    )
    setup_after = (
        "\tnor\t$2,$0,$19\n"
        "\tsra\t$2,$2,31\n"
        "\tmove\t$7,$19\n"
        "\tand\t$19,$19,$2\n"
    )
    text = _replace_once(text, setup_before, setup_after, "left-coordinate schedule")

    constants_before = (
        "\tli\t$16,0x00000083\t\t# 131\n"
        "\tli\t$19,0x00000057\t\t# 87\n"
    )
    constants_after = (
        "\tli\t$19,0x00000057\t\t# 87\n"
        "\tli\t$16,0x00000083\t\t# 131\n"
    )
    text = _replace_once(text, constants_before, constants_after, "text constants")

    scan_before = (
        ".L33:\n"
        "\tsll\t$2,$2,2\n"
        "\taddu\t$2,$16,$2\n"
        "\tla\t$14,D_803282A8\n"
        "\taddu\t$2,$2,$14\n"
    )
    scan_after = (
        ".L33:\n"
        "\tla\t$14,D_803282A8\n"
        "\taddu\t$3,$16,$14\n"
        "\tsll\t$2,$2,2\n"
        "\taddu\t$2,$2,$3\n"
    )
    text = _replace_once(text, scan_before, scan_after, "button-table address")

    text_before = (
        "\tlw\t$14,76($sp)\n"
        "\tlbu\t$2,0($21)\n"
        "\taddu\t$3,$14,$fp\n"
        "\tsll\t$2,$2,2\n"
        "\tlw\t$2,D_80135034($2)\n"
        "\taddu\t$19,$3,35\n"
        "\tla\t$3,D_80135034\n"
    )
    text_after = (
        "\tlw\t$14,76($sp)\n"
        "\tlbu\t$3,0($21)\n"
        "\taddu\t$2,$14,$fp\n"
        "\taddu\t$19,$2,35\n"
        "\tsll\t$3,$3,2\n"
        "\tlw\t$2,D_80135034($3)\n"
        "\tla\t$3,D_80135034\n"
    )
    text = _replace_once(text, text_before, text_after, "text-position schedule")

    return text, 1
