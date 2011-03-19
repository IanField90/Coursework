<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:output
method="html"
omit-xml-declaration="no"
doctype-public="-//W3C//DTD XHTML 1.1 Strict//EN"
doctype-system="http://www.w3.org/TR/xhtml1/Dtd/xhtml1-transitional.dtd"
indent="yes" />

	<xsl:template match="/">
		<html xmlns="http://www.w3.org/1999/xhtml">
			<head>
				<title>Bibtex citations</title>
				<link rel="stylesheet" type="text/css" href="stylesheet.css" />
			</head>
			<body>
				<xsl:for-each select="citations/article">
					<table>
						<tr>
							<th>Article entry:</th>
							<th><xsl:value-of select="attribute::name" /></th>
						</tr>						
						<tr>
							<td>Author</td>
							<td><xsl:value-of select="author" /></td>
						</tr>
						<tr>
							<td>Title</td>
							<td><xsl:value-of select="title" /></td>
						</tr>
						<tr>
							<td>Journal</td>
							<td><xsl:value-of select="journal" /></td>
						</tr>
						<tr>
							<td>Year</td>
							<td><xsl:value-of select="year" /></td>
						</tr>
						<tr>
							<td>Volume</td>
							<td><xsl:value-of select="volume" /></td>
						</tr>
						<tr>
							<td>Pages</td>
							<td><xsl:value-of select="pages" /></td>
						</tr>
						<tr>
							<td>Number</td>
							<td><xsl:value-of select="number" /></td>
						</tr>
						<tr>
							<td>Month</td>
							<td><xsl:value-of select="month" /></td>
						</tr>
						<tr>
							<td>DOI</td>
							<td><xsl:value-of select="doi" /></td>
						</tr>
						<tr>
							<td>Owner</td>
							<td><xsl:value-of select="owner" /></td>
						</tr>
						<tr>
							<td>Timestamp</td>
							<td><xsl:value-of select="timestamp" /></td>
						</tr>
						
					</table>
					<br />
				</xsl:for-each>
				
				<xsl:for-each select="citations/inproceedings">
					<table>
						<tr>
							<th>Inproceedings entry:</th>
							<th><xsl:value-of select="attribute::name" /></th>
						</tr>						
						<tr>
							<td>Author</td>
							<td><xsl:value-of select="author" /></td>
						</tr>
						<tr>
							<td>Title</td>
							<td><xsl:value-of select="title" /></td>
						</tr>
						<tr>
							<td>Booktitle</td>
							<td><xsl:value-of select="booktitle" /></td>
						</tr>
						<tr>
							<td>Year</td>
							<td><xsl:value-of select="year" /></td>
						</tr>
						<tr>
							<td>Pages</td>
							<td><xsl:value-of select="pages" /></td>
						</tr>
						<tr>
							<td>Month</td>
							<td><xsl:value-of select="month" /></td>
						</tr>
						<tr>
							<td>DOI</td>
							<td><xsl:value-of select="doi" /></td>
						</tr>
						<tr>
							<td>Owner</td>
							<td><xsl:value-of select="owner" /></td>
						</tr>
						<tr>
							<td>Timestamp</td>
							<td><xsl:value-of select="timestamp" /></td>
						</tr>
						
					</table>
					<br />
				</xsl:for-each>

			</body>
		</html>
	</xsl:template>

</xsl:stylesheet>