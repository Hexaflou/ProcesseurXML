<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <xsl:output method="html"/>
  
  <!-- Template pour la racine -->
	<xsl:template match="rapport">
		<html>
			<head>
				<title>
				  <xsl:value-of select="titre" />
				</title>
				<meta content="text/html; charset=UTF-8" http-equiv="Content-Type" />
			</head>
			<body bgColor="white">

			<xsl:apply-templates select="titre" />

			<ul>
				<xsl:apply-templates select="auteur" />
			</ul>			

			<xsl:apply-templates />

			</body>
		</html>
	</xsl:template>

	<!-- Template pour le titre -->
	<xsl:template match="titre">		
		<h1>
			<xsl:value-of select="." />
		</h1>			
	</xsl:template>

	<!-- Template pour les auteurs -->
	<xsl:template match="auteur">		
		<li>
			<xsl:value-of select="nom" /><xsl:text> </xsl:text><xsl:value-of select="prenom" />
		</li>			
	</xsl:template>

	<!-- Template pour le resume -->
	<xsl:template match="resume">
		<h2>
			Résumé
		</h2>
		<p><xsl:value-of select="resume" /></p>
	</xsl:template>

	<!-- Template pour les chapitres -->
	<xsl:template match="chapitre">		
		<xsl:if test="./@titre">
		<h2>
			<xsl:value-of select="@titre" />
		</h2>
		</xsl:if>			
	</xsl:template>
</xsl:stylesheet>