#!/usr/bin/env python3
"""
Programme pour ajouter un paramètre de roughness aux lignes de triangles RT
Ajoute "roughness_default=X" à la fin de chaque ligne tr
"""

import sys
import os


def add_roughness_to_line(line, roughness_value):
    """Ajoute le paramètre de roughness à une ligne tr"""
    line = line.strip()
    
    # Si ce n'est pas une ligne de triangle, la retourner telle quelle
    if not line.startswith('tr'):
        return line + '\n'
    
    # Ajouter le paramètre de roughness à la fin
    return f"{line} roughness_default={roughness_value}\n"


def add_roughness_to_file(input_file, output_file, roughness_value):
    """Ajoute le roughness à toutes les lignes tr d'un fichier RT"""
    triangles_processed = 0
    
    with open(input_file, 'r') as f_in, open(output_file, 'w') as f_out:
        for line in f_in:
            modified_line = add_roughness_to_line(line, roughness_value)
            f_out.write(modified_line)
            
            # Compter les triangles modifiés
            if line.strip().startswith('tr'):
                triangles_processed += 1
    
    return triangles_processed


def main():
    if len(sys.argv) < 2:
        print("Usage: python add_roughness.py <fichier.rt> [valeur_roughness] [fichier_sortie.rt]")
        print("\nValeur de roughness (défaut: 0.5)")
        print("\nExemples:")
        print("  python add_roughness.py model.rt              # Roughness 0.5 par défaut")
        print("  python add_roughness.py model.rt 0.8          # Roughness 0.8")
        print("  python add_roughness.py model.rt 0.3 out.rt   # Roughness 0.3, sortie vers out.rt")
        sys.exit(1)
    
    input_file = sys.argv[1]
    
    # Déterminer la valeur de roughness
    roughness_value = 0.5
    if len(sys.argv) >= 3:
        try:
            roughness_value = float(sys.argv[2])
        except ValueError:
            print(f"Erreur: Valeur de roughness invalide '{sys.argv[2]}'")
            sys.exit(1)
    
    # Déterminer le fichier de sortie
    if len(sys.argv) >= 4:
        output_file = sys.argv[3]
    else:
        # Par défaut, ajouter _roughness avant l'extension
        base, ext = os.path.splitext(input_file)
        output_file = f"{base}_roughness{ext}"
    
    # Vérifier que le fichier existe
    if not os.path.exists(input_file):
        print(f"Erreur: Le fichier '{input_file}' n'existe pas")
        sys.exit(1)
    
    print(f"Ajout de roughness au fichier: {input_file}")
    print(f"Valeur de roughness: {roughness_value}")
    print(f"Fichier de sortie: {output_file}")
    
    count = add_roughness_to_file(input_file, output_file, roughness_value)
    
    print(f"✓ Traitement terminé: {count} triangles modifiés")


if __name__ == "__main__":
    main()