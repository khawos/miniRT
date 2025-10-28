import re
from pathlib import Path

# === Chemins de fichiers ===
input_file = "/home/jbayonne/42/minirt/texture_file/AnyConv.com__wooden_gate_rough_2k.xpm"     # ton XPM original
output_file = "/home/jbayonne/42/minirt/texture_file/wooden_gate_rough_2k.xpm"  # fichier converti

# === Fonction de conversion 16 bits → 8 bits ===
def convert_color(code: str) -> str:
    """Convertit un code couleur #RRRRGGGGBBBB en #RRGGBB"""
    if len(code) == 13 and code.startswith("#"):
        r = code[1:5]
        g = code[5:9]
        b = code[9:13]
        # On prend les deux premiers hex de chaque canal (ou divise par 256)
        return f"#{r[:2]}{g[:2]}{b[:2]}".upper()
    elif len(code) == 7 and code.startswith("#"):
        # Déjà au bon format
        return code.upper()
    else:
        return code  # ne rien changer si ce n’est pas un code hexa

# === Lecture du fichier ===
text = Path(input_file).read_text(encoding="utf-8")

# === Remplacement des couleurs ===
pattern = re.compile(r'#(?:[0-9a-fA-F]{12}|[0-9a-fA-F]{6})')
converted_text = pattern.sub(lambda m: convert_color(m.group(0)), text)

# === Sauvegarde ===
Path(output_file).write_text(converted_text, encoding="utf-8")

print(f"✅ Conversion terminée !\n→ Fichier créé : {output_file}")
