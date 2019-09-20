# Logbuch 2DGameSDK

## 13.09.2019

### Status

- SceneGraph duale Struktur (tree, map) -> 2h
- AABB und Umrechnung Weltkoordinaten implementiert -> 3h 
  - Irrtum: Umrechnung ist nicht die Inverse Transformation -> +2h
- Kollisionsmasken implementiert -> 4h

### Ausblick

- SceneGraph muss refactored werden (keine Kapselung)
- Vorherzusehende Performance Probleme lösen:
  - Update AABB und Kollisionsmaske max. 1x pro tick (ideal: 1x pro Bewegung)

## 15.09.2019

### Status

- Chopper Demo aktualisiert -> 1h
- Github Kanban Board und Tasks erstellt -> 2h PM

## 16.09.2019

### Status

- SceneGraph Kapselung: Gesamte Logik nun im SceneGraph -> 2h

### Ausblick

- Sollte die Entity SceneGraphNode extenden?
- Sollte der SceneGraph die BewegungsLogik managen?
  - Child Entities würden nur bei Bewegung des Parents aktualisiert werden

## 18.09.2019

### Status

- Kickoff Meeting -> 1h PM
- Kollisionspunkt Berechnung implementiert -> 1h

### Ausblick

- Physik Engine POC
- ~~Kollisionspunkt Berechnung~~
- **Achtung:** Parallele Kanten können noch nicht kollidiert werden

## 20.09.2019

### Status

- Warnings auflösen (`-Wall`) -> 1h