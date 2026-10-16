"""Fail-closed two-phase normalization for update_effect_kind_5."""
from bt92734_pre_helper import normalize_bt92734_pre
from bt92734_list_aux_post import normalize_bt92734_list_aux
from bt92734_command_spatial import normalize_bt92734_command_spatial
from bt92734_command_outer import normalize_bt92734_command_outer
from bt92734_command_loop_target import normalize_bt92734_command_loop_target
from bt92734_descriptor_config_post import normalize_bt92734_descriptor_config
from bt92734_morph_stack_late_post import normalize_bt92734_morph_stack_late


def normalize_bt92734_post(text):
    """Apply currently available pure assembler-input rules in production order."""
    stages = (
        ("list-aux", normalize_bt92734_list_aux),
        ("command-spatial", normalize_bt92734_command_spatial),
        ("command-outer", normalize_bt92734_command_outer),
        ("command-loop-target", normalize_bt92734_command_loop_target),
        ("descriptor-config", normalize_bt92734_descriptor_config),
        ("morph-stack-late", normalize_bt92734_morph_stack_late),
    )
    fired = []
    for name, transform in stages:
        text, count = transform(text)
        if count != 1 and name != "morph-stack-late":
            raise RuntimeError(f"{name} unexpected fire count {count}")
        if name == "morph-stack-late" and count != 12:
            raise RuntimeError(f"{name} unexpected fire count {count}")
        fired.append(name)
    return text, tuple(fired)


__all__ = ("normalize_bt92734_pre", "normalize_bt92734_post")
