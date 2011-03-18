<?xml version="1.0"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:template match="/">
		<html>
			<head>
				<title>Bibtex citations</title>
				<link rel="stylesheet" type="text/css" href="stylesheet.css" />
			</head>
			<body>
				<xsl:for-each select="citations/article | citations/inproceedings">
					<table border="1" width="80%">
						<tr>
							<th>Entry Type:</th>
							<th><xsl:value-of select="parent::node/data"/></th>
						</tr>						
						<tr>
							<td>Author</td>
							<td><xsl:value-of select="author" /></td>
						</tr>
						<tr>
							<td>Title</td>
							<td><xsl:value-of select="title"/></td>
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
			</body>
		</html>
	</xsl:template>

</xsl:stylesheet>