#!/usr/bin/env python3
"""
Programme de translation de formes dans des fichiers RT
Déplace tous les triangles selon un vecteur de translation
"""

import sys
import os


def parse_rt_line(line):
    """Parse une ligne RT et retourne les données du triangle"""
    line = line.strip()
    if not line.startswith('tr'):
        return None
    
    # Enlever 'tr ' au début
    data = line[3:].strip().split()
    
    if len(data) != 4:
        return None
    
    # Parser les 3 points
    v1 = tuple(map(float, data[0].split(',')))
    v2 = tuple(map(float, data[1].split(',')))
    v3 = tuple(map(float, data[2].split(',')))
    
    # Parser la couleur
    color = data[3]
    
    return v1, v2, v3, color


def translate_point(point, translation):
    """Applique une translation à un point"""
    x, y, z = point
    tx, ty, tz = translation
    
    return (x + tx, y + ty, z + tz)


def format_rt_line(v1, v2, v3, color):
    """Formate une ligne RT"""
    return f"tr {v1[0]},{v1[1]},{v1[2]} {v2[0]},{v2[1]},{v2[2]} {v3[0]},{v3[1]},{v3[2]} {color}\n"


def translate_rt_file(input_file, output_file, translation):
    """Applique une translation à tous les triangles d'un fichier RT"""
    triangles_processed = 0
    
    with open(input_file, 'r') as f_in, open(output_file, 'w') as f_out:
        for line in f_in:
            parsed = parse_rt_line(line)
            
            if parsed is None:
                # Ligne non-triangle, la copier telle quelle
                f_out.write(line)
                continue
            
            v1, v2, v3, color = parsed
            
            # Appliquer la translation aux 3 points
            new_v1 = translate_point(v1, translation)
            new_v2 = translate_point(v2, translation)
            new_v3 = translate_point(v3, translation)
            
            # Écrire la ligne transformée
            f_out.write(format_rt_line(new_v1, new_v2, new_v3, color))
            triangles_processed += 1
    
    return triangles_processed


def main():
    if len(sys.argv) < 4:
        print("Usage: python translate_rt.py <fichier.rt> <tx> <ty> <tz> [fichier_sortie.rt]")
        print("\ntx, ty, tz: Vecteur de translation (x, y, z)")
        print("\nExemples:")
        print("  python translate_rt.py model.rt 1 0 0        # Translation de +1 sur X")
        print("  python translate_rt.py model.rt 0 2 0        # Translation de +2 sur Y")
        print("  python translate_rt.py model.rt 1 2 3        # Translation de +1,+2,+3")
        print("  python translate_rt.py model.rt -5 0 0       # Translation de -5 sur X")
        print("  python translate_rt.py model.rt 1 0 0 out.rt # Avec fichier de sortie")
        sys.exit(1)
    
    input_file = sys.argv[1]
    
    # Parser le vecteur de translation
    try:
        tx = float(sys.argv[2])
        ty = float(sys.argv[3])
        tz = float(sys.argv[4])
        translation = (tx, ty, tz)
    except (ValueError, IndexError):
        print("Erreur: Les valeurs de translation doivent être des nombres")
        print("Usage: python translate_rt.py <fichier.rt> <tx> <ty> <tz>")
        sys.exit(1)
    
    # Déterminer le fichier de sortie
    if len(sys.argv) >= 6:
        output_file = sys.argv[5]
    else:
        # Par défaut, ajouter _translated avant l'extension
        base, ext = os.path.splitext(input_file)
        output_file = f"{base}_translated{ext}"
    
    # Vérifier que le fichier existe
    if not os.path.exists(input_file):
        print(f"Erreur: Le fichier '{input_file}' n'existe pas")
        sys.exit(1)
    
    print(f"Translation du fichier: {input_file}")
    print(f"Vecteur de translation: ({tx}, {ty}, {tz})")
    print(f"Fichier de sortie: {output_file}")
    
    count = translate_rt_file(input_file, output_file, translation)
    
    print(f"✓ Translation terminée: {count} triangles déplacés")


if __name__ == "__main__":
    main()