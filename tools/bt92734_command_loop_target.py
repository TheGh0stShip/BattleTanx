"""Pure function-scoped command-loop target correction."""
import re

HEAD = re.compile(
    r"(?P<head>\.L\d+):\n"
    r"\tli\t\$12,-1207959552\t\t\t# 0xb8000000\n"
    r"\tli\t\$11,0x00000004\t\t# 4\n"
)


def normalize_bt92734_command_loop_target(text):
    start_marker = "func_80092734:\n"
    end_marker = "\t.end\tfunc_80092734\n"
    if text.count(start_marker) != 1 or text.count(end_marker) != 1:
        raise RuntimeError("BT92734 command-loop boundary count")
    start = text.index(start_marker)
    end = text.index(end_marker, start)
    head, body, tail = text[:start], text[start:end], text[end:]
    if ".Lcommand_body:" in body:
        raise RuntimeError("BT92734 command-loop destination already present")
    matches = list(HEAD.finditer(body))
    if len(matches) != 1:
        raise RuntimeError(f"BT92734 command-loop head fires {len(matches)}")
    match = matches[0]
    loop_head = match.group("head")
    branch = re.compile(
        rf"\tbne\t\$2,\$0,{re.escape(loop_head)}\n"
        rf"\tnop\n(?P<exit>\.L\d+):\n"
    )
    branches = list(branch.finditer(body))
    if len(branches) != 1:
        raise RuntimeError(f"BT92734 command-loop branch fires {len(branches)}")
    # Insert a private symbolic target immediately after the invariant setup,
    # then retarget only the uniquely paired back edge.
    body = body[:match.end()] + ".Lcommand_body:\n" + body[match.end():]
    branch_match = list(branch.finditer(body))
    if len(branch_match) != 1:
        raise RuntimeError("BT92734 command-loop branch moved unexpectedly")
    bm = branch_match[0]
    replacement = ("\tbne\t$2,$0,.Lcommand_body\n\tnop\n"
                   f"{bm.group('exit')}:\n")
    body = body[:bm.start()] + replacement + body[bm.end():]
    return head + body + tail, 1
