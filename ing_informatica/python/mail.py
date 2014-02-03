#! /usr/bin/env python

import smtplib
nome = "marco"
numeroTessera = 150
parolaChiave = "topo"


def prendiDati(nomeFile):
    file = open(nomeFile, "r")
    primariga = list(file.readline())
    nome = primariga[1]

    return nome


def scaricaMail()


def inviamail(ricevente, nome, numeroTessera, parolaChiave):
    mittente = "pscorso93@gmail.com"
    msg1 = """
Gentile  """ + nome + """,
=20
=20
Ti ringraziamo per la tua prenotazione per lo Snow Sonic festival 2014=20
=20
Il tuo numero di prenotazione e=92 701 - 702
tessera n. """ + numeroTessera + """
parola chiave:""" + parolaChiave + """
=20
=20
Ti preghiamo di conservare questa mail e di stamparla per poi esibirla =
al check in dell=92albergo Riceverai anche il bracciale per l=92accesso =
ai party del festival dopo aver compilato il modulo per iscriverti =
all=92ASD Forward Motion.
=20
Scrivendo a mail@forwardmotion.it ti preghiamo di indicarci anche:
-tutti  i nomi e cognomi dei partecipanti in caso di scelta multipla =
con rispettivo pacchetto scelto
=20
La struttura che ti/vi ospiter=E0=92 e=92 lo Stella Montis situato in =
Via Barcis 22, 33081 Piancavallo. L=92albergo e=92 situato vicino alla =
cassa centrale della stazione, al palaghiaccio ed allo snowpark.=20
=20
I pacchetto include:
=95      Tessera ASD Fwdmotion
=95      Pernottamento B&B oppure hotel ***=20
=95      Colazione
=95      WI-FI
=95      Bracciale per ingresso a tutti gli stage del festival
=95      Riduzione per skipass, noleggio, punti ristoro convenzionati, =
lezione scuola sci e snowboard
=20
I prezzi si intendono a persona per tipologia di camera tripla
=20
Eventuali supplementi verranno addebitati direttamente al check-in.
=20
SUPPLEMENTI:=20
-camera doppia uso singola maggiorazione di 15=80
-per camera doppia maggiorazione di 4=80
-mezza pensione maggiorazione di 10=80
=20
RIDUZIONI
-bambini fino ai 2 anni free
-" dai  3 ai 6  - 50%
-" dai 7 ai 12 - 20%
=20
IMPORTANTE
Per partecipare all=92evento e=92 obbligatorio essere iscritti all=92ASD =
forwardmotion.
Potrai compilare il modulo di iscrizione e poi ritirare il bracciale per =
l=92accesso a tutti gli stage dei parties presso gli info point degli =
alberghi o all=92ingresso dello snowpark presentando il voucher di =
prenotazione.
=20
CANCELLAZIONI
Le cancellazioni o le modifiche effettuate fino a 30 giorni prima della =
data prevista di arrivo  non comportano alcun costo.Le cancellazioni o =
le modifiche effettuate fino a 15 giorni prima della data prevista di =
arrivo  comportano l'addebito del 50 % dell'importo totale della =
prenotazione.Le cancellazioni o le modifiche tardive e la mancata =
presentazione comportano l'addebito del 100 % dell'importo totale della =
prenotazione.

Ti ringraziamo nuovamente per la tua partecipazione e ti auguriamo un =
buon soggiorno allo Snow Sonic 2014.bit_length


Rimaniamo a tua disposizione per ogni eventuale chiarimento.


Snow Sonic staff



Info
mail@forwardmotion.It
www.facebook.com/snowsonicfestival
twitter.Com/snowsonicfstvl
instagram/snowsonicfstvl
www.snowsonic.it

=A9 Copyright 2014 =B7 Snowsonic Festival=20
Brought To You By ASD Forward Motion.=20
Via Roma, 20 - Gorizia =B7 P.I.01132220318=.
"""
    gmail_pwd = "phil11235813213455"

    smtpserver = smtplib.SMTP("smtp.gmail.com", 587)
    smtpserver.ehlo()
    smtpserver.starttls()
    smtpserver.login(mittente, gmail_pwd)
    smtpserver.sendmail(mittente, ricevente, msg1)
    smtpserver.close()


def salva(ricevente, nome, numeroTessera, parolaChiave):
    file = open('lista_pagato.txt', 'a+')
    file.write(nome + " " + ricevente + "" + numeroTessera + " "
               + parolaChiave + "\n")
    file.close
